#include "SvgModelContainer.h"

bool SvgModelContainer::openDocument(const std::string &documentPath)
{
    if (this->svgDocuments.find(documentPath) != this->svgDocuments.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Document was already opened: \"" << documentPath << "\".").str();
        return false;
    }

    std::string source = IO::getInstance()->readAsString(documentPath);
    Ref<Svg::Document> document = Svg::Parser::parse(source);
    if (!document)
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Cannot read document: \"" << documentPath << "\". Document might be invalid.").str();
        return false;
    }
    this->svgDocuments[documentPath] = document;
    return true;
}

void SvgModelContainer::setQuality(VNint q)
{
    if (this->quality != q && q >= 0)
    {
        this->shouldReinitElements = true;
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
//    for (auto &model : this->models)
//    {
//        for (auto &element: model.second.elements)
//        {
//            const std::string &documentPath = element.documentName;
//            const std::string &layerName = element.layerName;
//            const Ref<Svg::Document> doc = this->svgDocuments[documentPath];
//            const Svg::Layer *layer = doc->getLayerByName(layerName);
//            element.vertices = Svg::Rasterizer::rasterize2D(layer, this->quality);
//        }
//        glm::vec2 modelBoundingBox = SvgModelContainer::getModelBoundingBox(model.second);
//        glm::vec2 modelCenter = Tools::Vertices2D::getCenter(model.second.elements[0].vertices);
//        for (auto &element: model.second.elements)
//        {
//            Tools::Vertices2D::applyVec2Sum(element.vertices, -modelCenter);
//            Tools::Vertices2D::normalize2DDimensions(element.vertices, modelBoundingBox);
//            element.borderMesh = MeshFactory::fromVertices(element.vertices.data(), element.vertices.size());
//            SvgModelContainer::updateElementTransformations(element);
//        }
//    }
}

void SvgModelContainer::update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta)
{
    interpolationSpeed = interpolationSpeed > 1.0f ? 1.0f : interpolationSpeed;
//    if (this->shouldReinitElements)
//    {
//        this->reset();
//        this->shouldReinitElements = false;
//    }
    for (auto &modelPair : this->models)
    {
        if (this->shouldModelBeUpdated(modelPair.second, floatInterpolationDelta))
        {
            this->updateModel(modelPair.second, floatInterpolationDelta, interpolationSpeed);
        }
    }
    this->shouldReinitElements = false;
//    {
//        bool elementsWasUpdated = false;
//        for (auto &modelElement : modelPair.second.elements)
//        {
//            bool elementUpdated = SvgModelContainer::shouldElementBeUpdated(modelElement);
//            if (elementUpdated)
//            {
//                elementsWasUpdated = true;
//                SvgModelContainer::updateElementTransformations(modelElement);
//            }
//        }
//        SvgModelContainer::Model &model = modelPair.second;
//        bool shouldUpdate = SvgModelContainer::shouldModelBeUpdated(model, floatInterpolationDelta);
//        if(!(shouldUpdate || elementsWasUpdated))
//        {
//            continue;
//        }
//        SvgModelContainer::interpolateModel(model, model.interpolatedVertices, false);
//        model.borderMesh = MeshFactory::fromVertices(model.interpolatedVertices.data(), model.interpolatedVertices.size());
//        model.triangulatedIndices = Tools::Vertices2D::triangulate(model.interpolatedVertices);
//        model.triangulatedMesh = MeshFactory::fromVerticesIndices(model.interpolatedVertices.data(), model.interpolatedVertices.size(),
//                                                                   model.triangulatedIndices.data(), model.triangulatedIndices.size());
//    }
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

bool SvgModelContainer::createModel(const std::string &modelName)
{
    if (this->models.find(modelName) != this->models.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Can't add model. Model with this name already exists: \"" << modelName <<"\".").str();
        return false;
    }
    this->models[modelName] = {};
    this->models[modelName].name = modelName;
    return true;
}

bool SvgModelContainer::addKeyedElementToGroup(const std::string &modelName, const std::string &keyedElementName, VNuint groupIndex)
{
    if (this->models.find(modelName) == this->models.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add keyed element to group. " <<
        "Can't add keyed element to group: no such model name. " <<
        "Model name: \"" << modelName <<"\"; " <<
        "Keyed element name: \"" << keyedElementName << "\"; " <<
        "Group index: " << groupIndex << ".").str();
        return false;
    }

    if (keyedElementName.empty())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add keyed element to group. " <<
             "Keyed element name is empty. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Keyed element name: \"" << keyedElementName << "\"; " <<
             "Group index: " << groupIndex << ".").str();
        return false;
    }

    Model &model = this->models[modelName];
    if (groupIndex >= model.groups.size())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add keyed element to group. " <<
             "Can't add keyed element to group: group index is greater than total number of groups. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Keyed element name: \"" << keyedElementName << "\"; " <<
             "Total groups: " << model.groups.size() << "; " <<
             "Group index: " << groupIndex << ".").str();
        return false;
    }

    Group &group = model.groups[groupIndex];
    KeyedElement newKeyedElement;
    newKeyedElement.name = keyedElementName;
    group.keyedElements.push_back(newKeyedElement);
    return true;
}

bool SvgModelContainer::addElementToKeyedElement(const std::string &modelName, const std::string &elementName,
                                                 const std::string &documentPath, const std::string &layerName,
                                                 VNuint groupIndex, VNuint keyedElementIndex)
{
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't add element to keyed element: no such document path. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << elementName << "\"; " <<
             "Group index: " << groupIndex << "; " <<
             "Keyed element index: " << keyedElementIndex << ".").str();
        return false;
    }

    Ref<Svg::Document> doc = this->svgDocuments[documentPath];
    if (doc->getLayerByName(layerName) == nullptr)
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't add element to keyed element: no such layer name in document. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << elementName << "\"; " <<
             "Group index: " << groupIndex << "; " <<
             "Keyed element index: " << keyedElementIndex << ".").str();
        return false;
    }

    if (this->models.find(modelName) == this->models.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't add element to keyed element: no such model name. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << elementName << "\"; " <<
             "Group index: " << groupIndex << "; " <<
             "Keyed element index: " << keyedElementIndex << ".").str();
        return false;
    }

    if (elementName.empty())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't add element to keyed element: element name is empty. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << elementName << "\"; " <<
             "Group index: " << groupIndex << "; " <<
             "Keyed element index: " << keyedElementIndex << ".").str();
        return false;
    }

    Model &model = this->models[modelName];
    if (groupIndex >= model.groups.size())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't add element to keyed element: group index is greater than total number of groups. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << elementName << "\"; " <<
             "Group index: " << groupIndex << "; " <<
             "Total group count: " << model.groups.size() << "; " <<
             "Keyed element index: " << keyedElementIndex << ".").str();
        return false;
    }

    Group &group = model.groups[groupIndex];
    if (keyedElementIndex >= group.keyedElements.size())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't add element to keyed element: keyed element index is greater than total number of keyed elements. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << elementName << "\"; " <<
             "Group index: " << groupIndex << "; " <<
             "Total keyed element count: " << group.keyedElements.size() << "; " <<
             "Keyed element index: " << keyedElementIndex << ".").str();
        return false;
    }

    KeyedElement &keyedElement = group.keyedElements[keyedElementIndex];
    Element newElement;
    newElement.layerName = layerName;
    newElement.documentPath = documentPath;
    newElement.name = elementName;
    keyedElement.keys.push_back(newElement);
    return true;
}

//bool SvgModelContainer::addElementToGroup(const std::string &modelName, const std::string &documentPath,
//                                          const std::string &layerName, VNuint groupIndex)
//{
//    if (this->models.find(modelName) == this->models.end())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add element to group. Can't add element to group: no such model name. " <<
//        "Model name: \"" << modelName <<"\"; " <<
//        "Document path: \"" << documentPath << "\"; " <<
//        "Layer name: \"" << layerName << "\"; " <<
//        "Group index: " << groupIndex << ".").str();
//        return false;
//    }
//
//    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add element to group. Can't add element to group: no such document. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupIndex << ".").str();
//        return false;
//    }
//    Ref<Svg::Document> doc = this->svgDocuments[documentPath];
//    const Svg::Layer *layer = doc->getLayerByName(layerName);
//    if (layer == nullptr)
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add element to group. Can't add element to group: no such layer in document. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupIndex << ".").str();
//        return false;
//    }
//    SvgModelContainer::Model &model = this->models[modelName];
//    if (groupIndex >= model.groups.size())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add element to group. Can't add element to group: no group with this index. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupIndex << "; " <<
//             "Total groups in model: " << model.groups.size() << ".").str();
//        return false;
//    }
//    SvgModelContainer::Group &group = model.groups[groupIndex];
//    SvgModelContainer::ModelElement svgElement = {documentPath, layerName};
//    svgElement.name = svgElement.layerName;
//    group.elements.push_back(svgElement);
//    return true;
//}

//bool SvgModelContainer::addIntermediateElementToElement(const std::string &modelName, const std::string &documentPath,
//                                                        const std::string &layerName, VNuint groupID, VNuint elementID)
//{
//    // If element is root element.
//    if (elementID == 0)
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add intermediate element to element. " <<
//             "Element index points to root element. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupID << "; " <<
//             "Element index: " << elementID << ".").str();
//        return false;
//    }
//    if (this->models.find(modelName) == this->models.end())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add intermediate element to element. " <<
//             "Cannot find model by name. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupID << "; " <<
//             "Element index: " << elementID << ".").str();
//        return false;
//    }
//    SvgModelContainer::Model &model = this->models[modelName];
//    if (groupID >= model.groups.size())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add intermediate element to element. " <<
//             "Group index is greater than model has groups. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupID << "; " <<
//             "Element index: " << elementID << "; " <<
//             "Total groups in model: " << model.groups.size() << ".").str();
//        return false;
//    }
//    SvgModelContainer::Group &group = model.groups[groupID];
//    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add intermediate element to element. " <<
//             "Cannot find document by path. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupID << "; " <<
//             "Element index: " << elementID << ".").str();
//        return false;
//    }
//    Ref<Svg::Document> doc = this->svgDocuments[documentPath];
//    const Svg::Layer *layer = doc->getLayerByName(layerName);
//    if (layer == nullptr)
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add intermediate element to element. " <<
//             "Cannot find layer in document by name. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupID << "; " <<
//             "Element index: " << elementID << ".").str();
//        return false;
//    }
//
//    if (elementID >= group.elements.size())
//    {
//        std::stringstream msg;
//        this->errorString = dynamic_cast<std::stringstream&>
//        (msg << "Add intermediate element to element. " <<
//             "Element ID is greater than total element count in group. " <<
//             "Model name: \"" << modelName <<"\"; " <<
//             "Document path: \"" << documentPath << "\"; " <<
//             "Layer name: \"" << layerName << "\"; " <<
//             "Group index: " << groupID << "; " <<
//             "Element index: " << elementID << "; " <<
//             "Total elements in group: " << group.elements.size() << ".").str();
//        return false;
//    }
//    SvgModelContainer::ModelElement *targetElement = &group.elements[elementID];
//    SvgModelContainer::ModelElement intermediateElement = {documentPath, layerName};
//    intermediateElement.name = intermediateElement.layerName;
//    targetElement->intermediateElements.push_back(intermediateElement);
//    return true;
//}

bool SvgModelContainer::addGroupToModel(const std::string &modelName, const std::string &groupName)
{
    if (this->models.find(modelName) == this->models.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add group to model. " <<
             "Cannot find model by name. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Group name: " << groupName << ".").str();
        return false;
    }
    if (groupName.empty())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add group to model. " <<
             "Group name is empty. " <<
             "Model name: \"" << modelName <<"\"; " <<
             "Group name: " << groupName << ".").str();
        return false;
    }
    Group newGroup;
    newGroup.name = groupName;
    this->models[modelName].groups.push_back(newGroup);
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

const std::string &SvgModelContainer::getErrorString()
{
    return this->errorString;
}

void SvgModelContainer::interpolateModel(Model &model, std::vector<VNfloat> &interpolationTarget, bool interpolateToTarget, VNfloat interpolationSpeed)
{
//    if (!interpolateToTarget)
//    {
//        // Update interpolations
//        for (VNuint i = 1; i < model.elements.size(); i++)
//        {
//            SvgModelContainer::ModelElement &element = model.elements[i];
//
//            element.interpolation = Math::lerp(element.interpolation, element.targetInterpolation, interpolationSpeed);
//        }
//    }
//    std::vector<VNfloat> interpolatedValues;
//    interpolatedValues.reserve(model.elements.size());
//    if (interpolationTarget.size() != model.elements[0].vertices.size())
//        interpolationTarget.resize(model.elements[0].vertices.size());
//
//    for (VNuint j = 0; j < model.elements[0].vertices.size(); j++)
//    {
//        SvgModelContainer::ModelElement &rootElement = model.elements[0];
//        for (VNuint i = 1; i < model.elements.size(); i++)
//        {
//            SvgModelContainer::ModelElement &secondElement = model.elements[i];
//
////            const VNfloat firstFloat = firstElement.vertices[j];
////            const VNfloat secondFloat = secondElement.vertices[j];
//            const VNfloat firstFloat = rootElement.transformedVertices[j];
//            const VNfloat secondFloat = secondElement.transformedVertices[j];
//            if (interpolateToTarget)
//                interpolatedValues.push_back((Math::lerp(firstFloat, secondFloat, secondElement.targetInterpolation) - firstFloat));
//            else
//                interpolatedValues.push_back((Math::lerp(firstFloat, secondFloat, secondElement.interpolation) - firstFloat));
//        }
//
////        interpolationTarget[j] = 0.0f;
//        interpolationTarget[j] = rootElement.transformedVertices[j];
//        for (VNuint k = 0; k < interpolatedValues.size(); k++)
//        {
//            interpolationTarget[j] += interpolatedValues[k];
////            interpolationTarget[j] += interpolatedValues[k];
//        }
//        interpolatedValues.clear();
//    }
}

bool SvgModelContainer::shouldModelBeUpdated(const Model &model, VNfloat floatDelta)
{
    if (model.groups.empty())
    {
        return false;
    }
    if (this->shouldReinitElements)
    {
        return true;
    }
    if (model.position != model.oldPosition ||
        model.rotation != model.oldRotation ||
        model.scale    != model.oldScale)
    {
        return true;
    }
    for (const auto &group : model.groups)
    {
        if (this->shouldGroupBeUpdated(group, floatDelta))
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldGroupBeUpdated(const Group &group, VNfloat floatDelta)
{
    if (group.keyedElements.empty())
    {
        return false;
    }
    if (this->shouldReinitElements)
    {
        return true;
    }
    if (group.interpolatedVertices.empty() ||
        group.triangulatedMesh == nullptr ||
        group.transformedBorderMesh == nullptr ||
        group.borderMesh == nullptr)
    {
        return true;
    }
    if (group.keyedElements.size() > 1)
    {
        if (group.keyedElementsInterpolations.size() != (group.keyedElements.size() - 1) ||
            group.targetKeyedElementsInterpolations.size() != (group.keyedElements.size() - 1))
        {
            return true;
        }
    }
    for (VNuint i = 0; i < group.keyedElementsInterpolations.size(); i++)
    {
        VNfloat interpolation = group.keyedElementsInterpolations[i];
        VNfloat targetInterpolation = group.targetKeyedElementsInterpolations[i];
        VNfloat delta = glm::abs(glm::abs(interpolation) - glm::abs(targetInterpolation));
        if (delta > floatDelta)
        {
            return true;
        }
    }
    if (group.position != group.oldPosition ||
        group.rotation != group.oldRotation ||
        group.scale != group.oldScale)
    {
        return true;
    }
    for (const auto &keyedElement : group.keyedElements)
    {
        if (this->shouldKeyedElementBeUpdated(keyedElement, floatDelta))
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldKeyedElementBeUpdated(const KeyedElement &keyedElement, VNfloat floatDelta)
{
    if (keyedElement.keys.empty())
    {
        return false;
    }
    for (const auto &key : keyedElement.keys)
    {
        if (SvgModelContainer::shouldElementBeUpdated(key))
        {
            return true;
        }
    }
    if (this->shouldReinitElements)
    {
        return true;
    }
    if (keyedElement.transformedVertices.empty() ||
        keyedElement.interpolatedVertices.empty() ||
        keyedElement.transformedBorderMesh == nullptr ||
        keyedElement.borderMesh == nullptr)
    {
        return true;
    }
    if (keyedElement.position != keyedElement.oldPosition ||
        keyedElement.rotation != keyedElement.oldRotation ||
        keyedElement.scale    != keyedElement.oldScale)
    {
        return true;
    }
    VNfloat delta = glm::abs(glm::abs(keyedElement.targetKeyPosition) - glm::abs(keyedElement.keyPosition));
    if (delta > floatDelta)
    {
        return true;
    }
    for (VNuint i = 0; i < keyedElement.keysPositions.size(); i++)
    {
        if (keyedElement.keysPositions[i] != keyedElement.oldKeysPositions[i])
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldElementBeUpdated(const Element &element, VNfloat floatDelta)
{
    if (this->shouldReinitElements)
    {
        return true;
    }
    if (element.position != element.oldPosition ||
        element.rotation != element.oldRotation ||
        element.scale    != element.oldScale)
    {
        return true;
    }
    if (element.transformedVertices.empty() ||
        element.vertices.empty() ||
        element.transformedBorderMesh == nullptr ||
        element.borderMesh == nullptr)
    {
        return true;
    }
    return false;
}

void SvgModelContainer::updateModel(Model &model, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    for (auto &group : model.groups)
    {
        if (this->shouldGroupBeUpdated(group, floatDelta))
        {
            this->updateGroup(group, floatDelta, interpolationSpeed);
        }
    }
    if((model.rotation != model.oldRotation) ||
       (model.scale    != model.oldScale))
    {
        model.scaleMatrix = {model.scale.x, 0.0f,
                            0.0f, model.scale.y};
        VNfloat radianRotation = glm::radians(model.rotation);
        model.rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
                                -glm::sin(radianRotation), glm::cos(radianRotation)};
        model.oldRotation = model.rotation;
        model.oldScale = model.scale;
    }
    if (model.position != model.oldPosition)
    {
        model.oldPosition = model.position;
    }
}

void SvgModelContainer::updateGroup(Group &group, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    bool keyedElementWasUpdated = false;
    for (auto &keyedElement : group.keyedElements)
    {
        if (this->shouldKeyedElementBeUpdated(keyedElement, floatDelta))
        {
            this->updateKeyedElement(keyedElement, floatDelta, interpolationSpeed);
            keyedElementWasUpdated = true;
        }
    }
    if (group.keyedElements.empty())
    {
        return;
    }
    group.keyedElementsInterpolations.resize(group.keyedElements.size());
    group.targetKeyedElementsInterpolations.resize(group.keyedElements.size());
    bool shouldDeltasBeUpdated = false;
    for (VNsize i = 0; i < group.keyedElementsInterpolations.size(); i++)
    {
        VNfloat interpolation = group.keyedElementsInterpolations[i];
        VNfloat targetInterpolation = group.targetKeyedElementsInterpolations[i];
        VNfloat delta = glm::abs(glm::abs(interpolation) - glm::abs(targetInterpolation));
        if (delta > floatDelta)
        {
            shouldDeltasBeUpdated = true;
            break;
        }
    }
    bool transformationChanged = (group.position != group.oldPosition) ||
                                 (group.rotation != group.oldRotation) ||
                                 (group.scale    != group.oldScale);
    if (!(shouldDeltasBeUpdated ||
        keyedElementWasUpdated ||
        group.interpolatedVertices.empty() ||
        group.borderMesh == nullptr ||
        group.transformedBorderMesh == nullptr ||
        transformationChanged))
    {
        return;
    }
    for (VNuint i = 0; i < group.keyedElementsInterpolations.size(); i++)
    {
        VNfloat interpolation = group.keyedElementsInterpolations[i];
        VNfloat targetInterpolation = group.targetKeyedElementsInterpolations[i];
        group.keyedElementsInterpolations[i] = Math::lerpDelta(interpolation, targetInterpolation, interpolationSpeed, floatDelta);
    }

    KeyedElement &rootKeyedElement = group.keyedElements[0];
    VNuint firstKeyedElementVerticesCount = rootKeyedElement.transformedVertices.size();
    group.interpolatedVertices.resize(firstKeyedElementVerticesCount);

    std::vector<VNfloat> interpolatedValues;
    interpolatedValues.resize(group.keyedElements.size());

    for (VNuint j = 0; j < firstKeyedElementVerticesCount; j++)
    {
        for (VNuint i = 1; i < group.keyedElements.size(); i++)
        {
            KeyedElement &targetKeyedElement = group.keyedElements[i];

            const VNfloat rootFloat = rootKeyedElement.transformedVertices[j];
            const VNfloat targetFloat = targetKeyedElement.transformedVertices[j];

            interpolatedValues[i - 1] = (Math::lerp(rootFloat, targetFloat, group.keyedElementsInterpolations[i - 1]) - rootFloat);
        }
        group.interpolatedVertices[j] = rootKeyedElement.transformedVertices[j];
        for (VNfloat interpolatedValue : interpolatedValues)
        {
            group.interpolatedVertices[j] += interpolatedValue;
        }
    }
    if(group.scale != group.oldScale)
    {
            group.scaleMatrix = {group.scale.x, 0.0f,
                                 0.0f, group.scale.y};
        group.oldScale = group.scale;
    }
    if(group.rotation != group.oldRotation)
    {
        VNfloat radianRotation = glm::radians(group.rotation);
        group.rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
                                -glm::sin(radianRotation), glm::cos(radianRotation)};

        group.oldRotation = group.rotation;

    }
    if (group.position != group.oldPosition)
    {
        group.oldPosition = group.position;
    }

    if (keyedElementWasUpdated)
    {
        group.borderMesh = MeshFactory::fromVertices(group.interpolatedVertices.data(),
                                                     group.interpolatedVertices.size(),
                                                     Mesh::PrimitiveType::Lines);
        SvgModelContainer::transformVertices(group.transformedVertices, group.interpolatedVertices,
                                             group.position,
                                             group.scale,
                                             group.rotation);
        group.transformedBorderMesh = MeshFactory::fromVertices(group.transformedVertices.data(),
                                                                group.transformedVertices.size(),
                                                                Mesh::PrimitiveType::Lines);
        std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(group.interpolatedVertices);
        group.triangulatedMesh = MeshFactory::fromVerticesIndices(group.interpolatedVertices.data(),
                                                                  group.interpolatedVertices.size(),
                                                                  triangulatedIndices.data(),
                                                                  triangulatedIndices.size(),
                                                                  Mesh::PrimitiveType::Triangles);
    }
}

void SvgModelContainer::updateKeyedElement(KeyedElement &keyedElement, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    bool elementWasUpdated = false;
    for (auto &key : keyedElement.keys)
    {
        if (this->shouldElementBeUpdated(key, floatDelta))
        {
            this->updateElement(key, floatDelta, interpolationSpeed);
            elementWasUpdated = true;
        }
    }
    if (keyedElement.keys.empty())
    {
        return;
    }
    bool keyChanged = false;
    keyedElement.keysPositions.resize(keyedElement.keys.size());
    keyedElement.oldKeysPositions.resize(keyedElement.keys.size());
    for (VNuint i = 0; i < keyedElement.keysPositions.size(); i++)
    {
        if (keyedElement.keysPositions[i] != keyedElement.oldKeysPositions[i])
        {
            keyChanged = true;
            break;
        }
    }
    bool shouldDeltaBeUpdated = false;
    VNfloat interpolation = keyedElement.keyPosition;
    VNfloat targetInterpolation = keyedElement.targetKeyPosition;
    VNfloat delta = glm::abs(glm::abs(interpolation) - glm::abs(targetInterpolation));
    if (delta > floatDelta)
    {
        shouldDeltaBeUpdated = true;
    }
    bool transformationChanged = (keyedElement.position != keyedElement.oldPosition) ||
                                 (keyedElement.rotation != keyedElement.oldRotation) ||
                                 (keyedElement.scale != keyedElement.oldScale);
    if (!(shouldDeltaBeUpdated ||
        elementWasUpdated ||
        keyedElement.transformedVertices.empty() ||
        keyedElement.interpolatedVertices.empty() ||
        keyedElement.borderMesh == nullptr ||
        keyedElement.transformedBorderMesh == nullptr ||
        keyChanged ||
        transformationChanged))
    {
        return;
    }
    if (shouldDeltaBeUpdated)
    {
        keyedElement.keyPosition = Math::lerp(interpolation, targetInterpolation, interpolationSpeed);
    }
    Element &rootElement = keyedElement.keys[0];
    VNuint firstElementVerticesCount = rootElement.transformedVertices.size();
    keyedElement.interpolatedVertices.resize(firstElementVerticesCount);
    keyedElement.transformedVertices.resize(firstElementVerticesCount);


    std::vector<std::pair<VNfloat, VNuint>> sortedKeys;
    sortedKeys.reserve(keyedElement.keys.size());
    for (VNuint index = 0; index < keyedElement.keysPositions.size(); index++)
    {
        VNfloat key = keyedElement.keysPositions[index];
        sortedKeys.emplace_back(key, index);
    }
    std::sort(sortedKeys.begin(), sortedKeys.end(), [](auto &a, auto &b){return a.first < b.first;});
    VNfloat keyPosition = keyedElement.keyPosition;
    VNuint keyIndex = 0;
    VNuint nextKeyIndex = 0;
    bool hasNextKey = false;
    if (keyPosition > sortedKeys[0].first)
    {
        for (VNuint index = 1; index < sortedKeys.size(); index++)
        {
            VNfloat keyPos = sortedKeys[index].first;
            if (keyPosition < keyPos)
            {
                keyIndex = sortedKeys[index - 1].second;
                nextKeyIndex = sortedKeys[index].second;
                hasNextKey = true;
                break;
            }
            if (index == sortedKeys.size() - 1)
            {
                keyIndex = sortedKeys[index].second;
                hasNextKey = false;
            }
        }
    }
    else
    {
        keyIndex = sortedKeys[0].second;
    }

//    for (auto &pair : sortedKeys)
//    {
//        printf("%f ", pair.first);
//    }
//    printf("\n");
    Element &key = keyedElement.keys[keyIndex];
    if (hasNextKey)
    {
//        printf("Has next key\n");
        VNfloat interpolationBetweenKeys;
        Element &nextKey = keyedElement.keys[nextKeyIndex];
        VNfloat previousKeyPosition = keyedElement.keysPositions[keyIndex];
        VNfloat nextKeyPosition = keyedElement.keysPositions[nextKeyIndex];
        interpolationBetweenKeys = keyPosition - previousKeyPosition;
        interpolationBetweenKeys = interpolationBetweenKeys / (nextKeyPosition - previousKeyPosition);
        keyedElement.interpolatedVertices.resize(key.transformedVertices.size());
        for (VNsize i = 0; i < keyedElement.interpolatedVertices.size(); i++)
        {
            VNfloat prevCoordinate = key.transformedVertices[i];
            VNfloat nextCoordinate = nextKey.transformedVertices[i];
            keyedElement.interpolatedVertices[i] = Math::lerp(prevCoordinate, nextCoordinate, interpolationBetweenKeys);
        }
    }
    else
    {
        keyedElement.interpolatedVertices = key.transformedVertices;
    }
    SvgModelContainer::transformVertices(keyedElement.transformedVertices, keyedElement.interpolatedVertices,
                                         keyedElement.position, keyedElement.scale, keyedElement.rotation);
    keyedElement.oldPosition = keyedElement.position;
    keyedElement.oldScale = keyedElement.scale;
    keyedElement.oldRotation = keyedElement.rotation;
    keyedElement.oldKeysPositions = keyedElement.keysPositions;

    keyedElement.borderMesh = MeshFactory::fromVertices(keyedElement.interpolatedVertices.data(),
                                                        keyedElement.interpolatedVertices.size(),
                                                        Mesh::PrimitiveType::Lines);
    keyedElement.transformedBorderMesh = MeshFactory::fromVertices(keyedElement.transformedVertices.data(),
                                                                   keyedElement.transformedVertices.size(),
                                                                   Mesh::PrimitiveType::Lines);
}

void SvgModelContainer::updateElement(Element &element, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    bool transformationChanged = (element.position != element.oldPosition) ||
                                 (element.rotation != element.oldRotation) ||
                                 (element.scale    != element.oldScale);
    if (!(this->shouldReinitElements ||
            element.transformedVertices.empty() ||
            element.vertices.empty() ||
            element.transformedBorderMesh == nullptr ||
            element.borderMesh == nullptr ||
            transformationChanged))
    {
        return;
    }
    const std::string &documentPath = element.documentPath;
    const std::string &layerName = element.layerName;
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end() ||
        this->svgDocuments[documentPath]->getLayerByName(layerName) == nullptr)
    {
        return;
    }
    if (this->shouldReinitElements ||
        element.vertices.empty())
    {
        Ref<Svg::Document> doc = this->svgDocuments[documentPath];
        const Svg::Layer *layer = doc->getLayerByName(layerName);

        element.vertices = Svg::Rasterizer::rasterize2D(layer, this->quality);
        Tools::Vertices2D::center2D(element.vertices);
        Tools::Vertices2D::normalize2D(element.vertices);
        Tools::Vertices2D::applyVec2Mul(element.vertices, glm::vec2(0.3f));
    }

    SvgModelContainer::transformVertices(element.transformedVertices,
                                         element.vertices,
                                         element.position,
                                         element.scale,
                                         element.rotation);
    element.borderMesh = MeshFactory::fromVertices(element.vertices.data(),
                                                   element.vertices.size(),
                                                   Mesh::PrimitiveType::Lines);
    element.transformedBorderMesh = MeshFactory::fromVertices(element.transformedVertices.data(),
                                                              element.transformedVertices.size(),
                                                              Mesh::PrimitiveType::Lines);
    element.oldPosition = element.position;
    element.oldScale    = element.scale;
    element.oldRotation = element.rotation;
}

void SvgModelContainer::transformVertices(std::vector<VNfloat> &destination, std::vector<VNfloat> &source, glm::vec2 &position, glm::vec2 &scale, VNfloat rotation)
{
    destination.resize(source.size());
    glm::mat2 scalingMatrix = {scale.x, 0.0f,
                               0.0f, scale.y};
    VNfloat radianRotation = glm::radians(rotation);
    glm::mat2 rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
                                -glm::sin(radianRotation), glm::cos(radianRotation)};
    glm::mat2 scalingRotationMatrix = rotationMatrix * scalingMatrix;
    for (VNsize index = 0; index < source.size(); index += 2)
    {
        glm::vec2 vertex = {source[index],
                            source[index + 1]};
        vertex = vertex * scalingRotationMatrix;
        destination[index] = vertex.x + position.x;
        destination[index + 1] = vertex.y + position.y;
    }
}

//void SvgModelContainer::updateElementTransformations(ModelElement &element)
//{
//    element.transformedVertices.resize(element.vertices.size());
//    glm::mat2 scalingMatrix = {element.scale.x, 0.0f,
//                               0.0f, element.scale.y};
//    VNfloat radianRotation = glm::radians(element.rotation);
//    glm::mat2 rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
//                                -glm::sin(radianRotation), glm::cos(radianRotation)};
//    glm::mat2 scalingRotationMatrix = rotationMatrix * scalingMatrix;
//    for (VNsize index = 0; index < element.vertices.size(); index += 2)
//    {
//        glm::vec2 vertex = {element.vertices[index],
//                            element.vertices[index + 1]};
//        vertex = vertex * scalingRotationMatrix;
//        vertex += element.position;
//        element.transformedVertices[index] = vertex.x;
//        element.transformedVertices[index + 1] = vertex.y;
//    }
//    element.oldPosition = element.position;
//    element.oldScale = element.scale;
//    element.oldRotation = element.rotation;
//    element.transformedBorderMesh = MeshFactory::fromVertices(element.transformedVertices.data(), element.transformedVertices.size());
//}
