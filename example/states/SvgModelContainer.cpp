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

void SvgModelContainer::setQuality(VNint quality)
{
    if (this->quality == quality)
        return;
    this->quality = quality;
    this->forceUpdateAll();
}

void SvgModelContainer::closeDocument(const std::string &documentPath)
{
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
        return;
}

void SvgModelContainer::forceUpdateAll()
{

}

void SvgModelContainer::update()
{

    for (const std::string &modelName : this->modelsToUpdate)
    {
        if (this->models.find(modelName) == this->models.end())
            continue;
        SvgModelContainer::Model *model = &this->models[modelName];
        std::vector<VNfloat> interpolatedValues;
        interpolatedValues.reserve(model->elements.size());

        for (VNuint j = 0; j < model->elements[0].vertices.size(); j++)
        {
            for (VNuint i = 1; i < model->elements.size(); i++)
            {
                SvgModelContainer::ModelElement &firstElement = model->elements[0];
                SvgModelContainer::ModelElement &secondElement = model->elements[i];

                const VNfloat firstFloat = firstElement.vertices[j];
                const VNfloat secondFloat = secondElement.vertices[j];
                const VNfloat interpolationValue = secondElement.interpolation;
                interpolatedValues.push_back(Math::lerp(firstFloat, secondFloat, interpolationValue));
            }
            model->interpolatedVertices[j] = 0.0f;
            for (VNuint k = 0; k < interpolatedValues.size(); k++)
            {
                model->interpolatedVertices[j] += interpolatedValues[k] / (VNfloat)interpolatedValues.size();
            }
            model->interpolatedVertices.clear();
        }
        model->triangulatedIndices = Tools::Vertices2D::triangulate(model->interpolatedVertices);
        model->triangulatedMesh = MeshFactory::fromVerticesIndices(model->interpolatedVertices.data(), model->interpolatedVertices.size(),
                                                                   model->triangulatedIndices.data(), model->triangulatedIndices.size());
    }
    this->modelsToUpdate.clear();
}

void SvgModelContainer::scheduleModelUpdate(const std::string &modelName)
{
    this->modelsToUpdate.emplace(modelName);
}

std::unordered_map<std::string, SvgModelContainer::Model> *SvgModelContainer::getModels()
{
    return &this->models;
}

std::unordered_map<std::string, Ref<Svg::Document>> *SvgModelContainer::getDocuments()
{
    return &this->svgDocuments;
}

std::string SvgModelContainer::createModel()
{
    std::string modelName = Tools::randomString(10);
    this->models[modelName] = {};
    return modelName;
}

bool SvgModelContainer::addElementToModel(const std::string &modelName, const std::string &documentPath,
                                          const std::string &layerName)
{
    if (this->models.find(modelName) == this->models.end())
        return false;
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
        return false;
    const Svg::Layer *layer = this->svgDocuments[documentPath]->getLayerByName(layerName);
    if (layer == nullptr)
        return false;
    SvgModelContainer::Model &model = this->models[modelName];
    SvgModelContainer::ModelElement modelElement = {documentPath, layerName};
    modelElement.vertices = Svg::Rasterizer::rasterize2D(layer, this->quality);
    if (!model.elements.empty())
    {
        if (model.elements[0].vertices.size() != modelElement.vertices.size())
        {
            VAN_USER_INFO("addElementToModel: {}/{}/{}: vertices size does not match!", modelName, documentPath, layerName);
            return false;
        }
    }
    model.elements.push_back(modelElement);
    return true;
}

SvgModelContainer::Model *SvgModelContainer::getModelByName(const std::string &modelName)
{
    if (this->models.find(modelName) == this->models.end())
        return nullptr;
    return &this->models[modelName];
}
