#include "SvgModelContainer.h"

bool SvgModelContainer::openDocument(const std::string &documentPath)
{
    if (this->svgDocuments.find(documentPath) != this->svgDocuments.end())
        return false;
    std::string source = IO::getInstance()->readAsString(documentPath);
    Ref<Svg::Document> document = Svg::Parser::parse(source);

    if (!document)
        return false;
    this->svgDocuments[documentPath] = document;
    return true;
}

void SvgModelContainer::setQuality(VNint q)
{
    if (this->quality != q && q >= 0)
    {
        this->qualityChanged = true;
        this->quality = q;
    }
}

void SvgModelContainer::closeDocument(const std::string &documentPath)
{
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
        return;
}

void SvgModelContainer::reset()
{
    for (auto &model : this->models)
    {
        for (auto &element: model.second.elements)
        {
            const std::string &documentPath = element.documentName;
            const std::string &layerName = element.layerName;
            const Ref<Svg::Document> doc = this->svgDocuments[documentPath];
            const Svg::Layer *layer = doc->getLayerByName(layerName);
            element.vertices = Svg::Rasterizer::rasterize2D(layer, this->quality);
            Tools::Vertices2D::center2D(element.vertices);
            Tools::Vertices2D::normalize2DDimensions(element.vertices, doc->getDimensions());
            element.borderMesh = MeshFactory::fromVertices(element.vertices.data(), element.vertices.size());
            SvgModelContainer::updateElement(element);
        }
    }
}

void SvgModelContainer::update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta)
{
    interpolationSpeed = interpolationSpeed > 1.0f ? 1.0f : interpolationSpeed;
    if (this->qualityChanged)
    {
        this->reset();
        this->qualityChanged = false;
    }
    for (auto &modelPair : this->models)
    {
        for (auto &modelElement : modelPair.second.elements)
        {
            if (SvgModelContainer::shouldElementBeUpdated(modelElement))
            {
                SvgModelContainer::updateElement(modelElement);
            }
        }
        SvgModelContainer::Model &model = modelPair.second;
        bool shouldUpdate = SvgModelContainer::shouldModelBeUpdated(model, floatInterpolationDelta);
        if(!shouldUpdate)
        {
            continue;
        }
        SvgModelContainer::interpolateModel(model, model.interpolatedVertices, false);
        model.borderMesh = MeshFactory::fromVertices(model.interpolatedVertices.data(), model.interpolatedVertices.size());
        model.triangulatedIndices = Tools::Vertices2D::triangulate(model.interpolatedVertices);
        model.triangulatedMesh = MeshFactory::fromVerticesIndices(model.interpolatedVertices.data(), model.interpolatedVertices.size(),
                                                                   model.triangulatedIndices.data(), model.triangulatedIndices.size());
    }
}

std::unordered_map<std::string, SvgModelContainer::Model> &SvgModelContainer::getModels()
{
    return this->models;
}

std::unordered_map<std::string, Ref<Svg::Document>> &SvgModelContainer::getDocuments()
{
    return this->svgDocuments;
}

Ref<Svg::Document> SvgModelContainer::getDocumentByIndex(VNsize index)
{
    VNsize currIndex = 0;
    for (auto &docPair : this->svgDocuments)
    {
        if (currIndex == index)
        {
            return docPair.second;
        }
        currIndex++;
    }
    return nullptr;
}

std::string SvgModelContainer::getDocumentPathByIndex(VNsize index)
{
    VNsize currIndex = 0;

    for (auto &docPair : this->svgDocuments)
    {
        if (currIndex == index)
        {
            return docPair.first;
        }
        currIndex++;
    }
    return std::string();
}

std::string SvgModelContainer::createModel()
{
    std::string modelName = Tools::randomString(10);
    this->models[modelName] = {};
    return modelName;
}

bool SvgModelContainer::addElementToModel(const std::string &modelName, const std::string &documentPath,
                                          const std::string &layerName, bool flipY)
{
    if (this->models.find(modelName) == this->models.end())
        return false;
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
        return false;
    const Svg::Layer *layer = this->svgDocuments[documentPath]->getLayerByName(layerName);
    if (layer == nullptr)
        return false;
    Ref<Svg::Document> doc = this->svgDocuments[documentPath];
    SvgModelContainer::Model &model = this->models[modelName];
    SvgModelContainer::ModelElement modelElement = {documentPath, layerName};
    modelElement.name = modelElement.layerName;
    modelElement.vertices = Svg::Rasterizer::rasterize2D(layer, this->quality);
    if (!model.elements.empty())
    {
        if (model.elements[0].vertices.size() != modelElement.vertices.size())
        {
            VAN_USER_INFO("addElementToModel: {}/{}/{}: vertices size does not match!", modelName, documentPath, layerName);
            return false;
        }
    }
    Tools::Vertices2D::center2D(modelElement.vertices);
    Tools::Vertices2D::normalize2DDimensions(modelElement.vertices, doc->getDimensions());
    model.elements.push_back(modelElement);
    return true;
}

SvgModelContainer::Model *SvgModelContainer::getModelByName(const std::string &modelName)
{
    if (this->models.find(modelName) == this->models.end())
        return nullptr;
    return &this->models[modelName];
}

SvgModelContainer::Model *SvgModelContainer::getModelByIndex(VNsize index)
{
    VNsize i = 0;

    for (auto &model : this->models)
    {
        if (index == i)
            return &model.second;
        i++;
    }
    return nullptr;
}

std::string SvgModelContainer::getModelNameByIndex(VNsize index)
{
    VNsize i = 0;

    for (auto &model : this->models)
    {
        if (index == i)
            return model.first;
        i++;
    }
    return std::string();
}

void SvgModelContainer::interpolateModel(Model &model, std::vector<VNfloat> &interpolationTarget, bool interpolateToTarget, VNfloat interpolationSpeed)
{
    if (!interpolateToTarget)
    {
        // Update interpolations
        for (VNuint i = 1; i < model.elements.size(); i++)
        {
            SvgModelContainer::ModelElement &element = model.elements[i];

            element.interpolation = Math::lerp(element.interpolation, element.targetInterpolation, interpolationSpeed);
        }
    }
    std::vector<VNfloat> interpolatedValues;
    interpolatedValues.reserve(model.elements.size());
    if (interpolationTarget.size() != model.elements[0].vertices.size())
        interpolationTarget.resize(model.elements[0].vertices.size());

    for (VNuint j = 0; j < model.elements[0].vertices.size(); j++)
    {
        for (VNuint i = 1; i < model.elements.size(); i++)
        {
            SvgModelContainer::ModelElement &firstElement = model.elements[0];
            SvgModelContainer::ModelElement &secondElement = model.elements[i];

            const VNfloat firstFloat = firstElement.vertices[j];
            const VNfloat secondFloat = secondElement.vertices[j];
            if (interpolateToTarget)
                interpolatedValues.push_back(Math::lerp(firstFloat, secondFloat, secondElement.targetInterpolation));
            else
                interpolatedValues.push_back(Math::lerp(firstFloat, secondFloat, secondElement.interpolation));
        }
        interpolationTarget[j] = 0.0f;
        for (VNuint k = 0; k < interpolatedValues.size(); k++)
        {
            interpolationTarget[j] += interpolatedValues[k] / (VNfloat)interpolatedValues.size();
        }
        interpolatedValues.clear();
    }
}

bool SvgModelContainer::shouldModelBeUpdated(const Model &model, VNfloat floatDelta)
{
    if (model.interpolatedVertices.empty())
        return true;
    if (model.elements.empty())
        return false;
    if (model.interpolatedVertices.size() != model.elements.begin()->vertices.size())
        return true;
    for (const auto &element : model.elements)
    {
        if (SvgModelContainer::shouldElementBeUpdated(element))
            return true;
        VNfloat delta = glm::abs(glm::abs(element.targetInterpolation) - glm::abs(element.interpolation));
        if (delta > floatDelta)
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldElementBeUpdated(const ModelElement &element)
{
    if (element.rotation != element.oldRotation ||
        element.scale != element.oldScale ||
        element.position != element.oldPosition)
    {
        return true;
    }
    if (element.transformedVertices.empty() ||
        element.vertices.empty())
    {
        return true;
    }
    if (element.borderMesh == nullptr ||
        element.transformedBorderMesh == nullptr)
    {
        return false;
    }
}

void SvgModelContainer::updateElement(ModelElement &element)
{
    element.transformedVertices.resize(element.vertices.size());
    glm::mat2 scalingMatrix = {element.scale.x, 0.0f,
                               0.0f, element.scale.y};
    VNfloat radianRotation = glm::radians(element.rotation);
    glm::mat2 rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
                                -glm::sin(radianRotation), glm::cos(radianRotation)};
    glm::mat2 scalingRotationMatrix = scalingMatrix * rotationMatrix;
    for (VNsize index = 0; index < element.vertices.size(); index += 2)
    {
        glm::vec2 vertex = {element.vertices[index],
                            element.vertices[index + 1]};
        vertex = vertex * scalingRotationMatrix;
        vertex += element.position;
        element.transformedVertices[index] = vertex.x;
        element.transformedVertices[index + 1] = vertex.y;
    }
    element.oldPosition = element.position;
    element.oldScale = element.scale;
    element.oldRotation = element.rotation;
    element.transformedBorderMesh = MeshFactory::fromVertices(element.transformedVertices.data(), element.transformedVertices.size());
}