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
        this->qualityChanged = true;
        this->quality = q;
    }
}

void SvgModelContainer::closeDocument(const std::string &documentPath)
{
    auto foundDocument = this->svgDocuments.find(documentPath);
    if (foundDocument == this->svgDocuments.end())
        return;
    this->svgDocuments.erase(foundDocument);
}

void SvgModelContainer::update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta)
{
    interpolationSpeed = interpolationSpeed > 1.0f ? 1.0f : interpolationSpeed;
    for (auto modelID : this->modelIDs)
    {
        if (this->shouldModelBeUpdated(modelID, floatInterpolationDelta))
        {
            this->updateModel(modelID, floatInterpolationDelta, interpolationSpeed);
        }
    }
    this->qualityChanged = false;
}

std::unordered_map<size_t, Ref<SvgModel::Object>> &SvgModelContainer::getScene()
{
    return this->scene;
}

Ref<SvgModel::Model> SvgModelContainer::getModel(size_t id)
{
    auto found = this->scene.find(id);

    if (found == this->scene.end())
    {
        return nullptr;
    }
    if (found->second->getType() != SvgModel::ModelType::Model)
    {
        return nullptr;
    }
    return std::dynamic_pointer_cast<SvgModel::Model>(found->second);
}

Ref<SvgModel::Group> SvgModelContainer::getGroup(size_t id)
{
    auto found = this->scene.find(id);

    if (found == this->scene.end())
    {
        return nullptr;
    }
    if (found->second->getType() != SvgModel::ModelType::Group)
    {
        return nullptr;
    }
    return std::dynamic_pointer_cast<SvgModel::Group>(found->second);
}

Ref<SvgModel::KeyedElement> SvgModelContainer::getKeyedElement(size_t id)
{
    auto found = this->scene.find(id);

    if (found == this->scene.end())
    {
        return nullptr;
    }
    if (found->second->getType() != SvgModel::ModelType::KeyedElement)
    {
        return nullptr;
    }
    return std::dynamic_pointer_cast<SvgModel::KeyedElement>(found->second);
}

Ref<SvgModel::Key> SvgModelContainer::getKey(size_t id)
{
    auto found = this->scene.find(id);

    if (found == this->scene.end())
    {
        return nullptr;
    }
    if (found->second->getType() != SvgModel::ModelType::Key)
    {
        return nullptr;
    }
    return std::dynamic_pointer_cast<SvgModel::Key>(found->second);
}

Ref<SvgModel::Object> SvgModelContainer::getObject(size_t id)
{
    auto found = this->scene.find(id);

    if (found == this->scene.end())
    {
        return nullptr;
    }
    return found->second;
}

const std::vector<size_t> &SvgModelContainer::getModelsIDs()
{
    return this->modelIDs;
}

const std::vector<size_t> &SvgModelContainer::getGroupsIDs()
{
    this->groupsIDs;
}

const std::vector<size_t> &SvgModelContainer::getKeyedElementsIDs()
{
    this->keyedElementsIDs;
}

const std::vector<size_t> &SvgModelContainer::getKeysIDs()
{
    this->keyIDs;
}

const std::unordered_map<std::string, Ref<Svg::Document>> &SvgModelContainer::getDocuments()
{
    return this->svgDocuments;
}

SvgModel::ModelType SvgModelContainer::getType(size_t id)
{
    auto found = this->scene.find(id);

    if (found == this->scene.end())
    {
        return SvgModel::ModelType::None;
    }
    return found->second->getType();
}
void SvgModelContainer::centerObjectToChildren(size_t id)
{
    Ref<SvgModel::Object> object = this->getObject(id);
    if (object == nullptr)
    {
        return;
    }
    if (object->getType() == SvgModel::ModelType::KeyedElement)
    {
        Ref<SvgModel::KeyedElement> keyedElementObject = std::dynamic_pointer_cast<SvgModel::KeyedElement>(object);
        glm::vec2 objectPos = keyedElementObject->position;
        VNfloat totalValidKeys = 0.0f;
        glm::vec2 accumulatedPosition = glm::vec2(0.0f);
        for (size_t keyID : keyedElementObject->keysIDs)
        {
            Ref<SvgModel::Key> keyObject = this->getKey(keyID);
            if (keyObject == nullptr)
            {
                continue;
            }
            totalValidKeys += 1.0f;
            accumulatedPosition += keyObject->position;
        }
        accumulatedPosition /= totalValidKeys;
        keyedElementObject->position += accumulatedPosition;
        for (size_t keyID : keyedElementObject->keysIDs)
        {
            Ref<SvgModel::Key> keyObject = this->getKey(keyID);
            if (keyObject == nullptr)
            {
                continue;
            }
            keyObject->position -= accumulatedPosition;
        }
    }
}
//
//Ref<Svg::Document> SvgModelContainer::getDocumentByIndex(VNsize index)
//{
//    VNsize currIndex = 0;
//    for (auto &docPair : this->svgDocuments)
//    {
//        if (currIndex == index)
//        {
//            return docPair.second;
//        }
//        currIndex++;
//    }
//    return nullptr;
//}
//
//std::string SvgModelContainer::getDocumentPathByIndex(VNsize index)
//{
//    VNsize currIndex = 0;
//
//    for (auto &docPair : this->svgDocuments)
//    {
//        if (currIndex == index)
//        {
//            return docPair.first;
//        }
//        currIndex++;
//    }
//    return std::string();
//}

size_t SvgModelContainer::addModel(const std::string &name)
{
    Ref<SvgModel::Model> newModel = MakeRef<SvgModel::Model>();
    newModel->id = hashString(Tools::randomString(20));
    if (name.empty())
    {
        newModel->name = "New model " + std::to_string(this->modelIDs.size() + 1);
    }
    else
    {
        newModel->name = name;
    }
    this->scene[newModel->id] = newModel;
    this->modelIDs.push_back(newModel->id);
    return newModel->id;
}

size_t SvgModelContainer::addGroup(size_t modelID, const std::string &name)
{
    auto foundModel = this->scene.find(modelID);

    if (foundModel == this->scene.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add group to model. " <<
             "Cannot find model by ID. " <<
             "Object ID: \"" << modelID << "\"; " <<
             "Group name: " << name << ".").str();
        return 0;
    }
    if (foundModel->second->getType() != SvgModel::ModelType::Model)
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add group to model. " <<
             "Found object is not a model. " <<
             "Object ID: \"" << modelID << "\"; " <<
             "Group name: " << name << ".").str();
        return 0;
    }
    Ref<SvgModel::Group> newGroup = MakeRef<SvgModel::Group>();
    newGroup->parentID = modelID;
    newGroup->id = hashString(Tools::randomString(20));
    if (name.empty())
    {
        newGroup->name = "New group " + std::to_string(this->groupsIDs.size() + 1);
    }
    else
    {
        newGroup->name = name;
    }
    this->scene[newGroup->id] = newGroup;
    this->groupsIDs.push_back(newGroup->id);
    Ref<SvgModel::Model> model = std::dynamic_pointer_cast<SvgModel::Model>(foundModel->second);
    model->groupsIDs.push_back(newGroup->id);
    return newGroup->id;
}

size_t SvgModelContainer::addKeyedElement(size_t groupID, const std::string &name)
{
    auto foundGroup = this->scene.find(groupID);
    if (foundGroup == this->scene.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add keyed element to group. " <<
             "Object by ID was not found. " <<
             "Object ID: \"" << groupID << "\"; " <<
             "Keyed element name: " << name << ".").str();
        return 0;
    }
    if (foundGroup->second->getType() != SvgModel::ModelType::Group)
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add keyed element to group. " <<
             "Found object is not a group object. " <<
             "Object ID: \"" << groupID << "\"; " <<
             "Keyed element name: " << name << ".").str();
        return 0;
    }
    Ref<SvgModel::KeyedElement> newKeyedElement = MakeRef<SvgModel::KeyedElement>();
    newKeyedElement->parentID = groupID;
    newKeyedElement->id = hashString(Tools::randomString(20));
    if (name.empty())
    {
        newKeyedElement->name = "New keyed element " + std::to_string(this->keyedElementsIDs.size() + 1 );
    }
    else
    {
        newKeyedElement->name = name;
    }
    this->scene[newKeyedElement->id] = newKeyedElement;
    this->keyedElementsIDs.push_back(newKeyedElement->id);
    Ref<SvgModel::Group> group = std::dynamic_pointer_cast<SvgModel::Group>(foundGroup->second);
    group->keyedElementsIDs.push_back(newKeyedElement->id);
    return newKeyedElement->id;
}

size_t SvgModelContainer::addKey(const std::string &documentPath,
                                 const std::string &layerName,
                                 size_t keyedElementID,
                                 const std::string &name)
{
    auto foundKeyedElement = this->scene.find(keyedElementID);
    if (foundKeyedElement == this->scene.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Can't find keyed element by ID. " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << name << "\"; " <<
             "Object ID: " << keyedElementID << ".").str();
        return 0;
    }
    if (foundKeyedElement->second->getType() != SvgModel::ModelType::KeyedElement)
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Found object by ID is not a keyed element. " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << name << "\"; " <<
             "Object ID: " << keyedElementID << ".").str();
        return 0;
    }
    auto document = this->svgDocuments.find(documentPath);
    if (document == this->svgDocuments.end())
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Document with path was not found. " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << name << "\"; " <<
             "Object ID: " << keyedElementID << ".").str();
        return 0;
    }
    auto *layer = document->second->getLayerByName(layerName);
    if (layer == nullptr)
    {
        std::stringstream msg;
        this->errorString = dynamic_cast<std::stringstream&>
        (msg << "Add element to keyed element. " <<
             "Layer with name was not found. " <<
             "Document path: \"" << documentPath << "\"; " <<
             "Layer name: \"" << layerName << "\"; " <<
             "Element name: \"" << name << "\"; " <<
             "Object ID: " << keyedElementID << ".").str();
        return 0;
    }
    Ref<SvgModel::Key> newElement = MakeRef<SvgModel::Key>();
    newElement->parentID = keyedElementID;
    newElement->id = hashString(Tools::randomString(20));
    if (name.empty())
    {
        newElement->name = "New key " + std::to_string(this->keyIDs.size() + 1);
    }
    else
    {
        newElement->name = name;
    }

    newElement->documentPath = documentPath;
    newElement->layerName = layerName;
    Ref<SvgModel::KeyedElement> keyedElement = std::dynamic_pointer_cast<SvgModel::KeyedElement>(foundKeyedElement->second);
    keyedElement->keysIDs.push_back(newElement->id);
    this->keyIDs.push_back(newElement->id);
    this->scene[newElement->id] = newElement;
    return newElement->id;
}

const std::string &SvgModelContainer::getErrorString()
{
    return this->errorString;
}

//void SvgModelContainer::interpolateModel(Model &model, std::vector<VNfloat> &interpolationTarget, bool interpolateToTarget, VNfloat interpolationSpeed)
//{
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
//}

bool SvgModelContainer::shouldModelBeUpdated(size_t id, VNfloat floatDelta)
{
    auto foundModel = this->scene.find(id);
    if (foundModel == this->scene.end())
    {
        return false;
    }
    if (foundModel->second->getType() != SvgModel::ModelType::Model)
    {
        return false;
    }
    Ref<SvgModel::Model> model = std::dynamic_pointer_cast<SvgModel::Model>(foundModel->second);
    if (model->groupsIDs.empty())
    {
        return false;
    }
    if (this->qualityChanged)
    {
        return true;
    }
    if (model->position != model->oldPosition ||
        model->rotation != model->oldRotation ||
        model->scale    != model->oldScale)
    {
        return true;
    }
    for (auto groupID : model->groupsIDs)
    {
        if (this->shouldGroupBeUpdated(groupID, floatDelta))
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldGroupBeUpdated(size_t id, VNfloat floatDelta)
{
    auto foundGroup = this->scene.find(id);
    if (foundGroup == this->scene.end())
    {
        return false;
    }
    if (foundGroup->second->getType() != SvgModel::ModelType::Group)
    {
        return false;
    }
    Ref<SvgModel::Group> group = std::dynamic_pointer_cast<SvgModel::Group>(foundGroup->second);
    if (group->keyedElementsIDs.empty())
    {
        return false;
    }
    if (this->qualityChanged)
    {
        return true;
    }
    if (group->interpolatedVertices.empty() ||
        group->triangulatedMesh == nullptr ||
        group->transformedBorderMesh == nullptr ||
        group->borderMesh == nullptr)
    {
        return true;
    }
    if (group->keyedElementsIDs.size() > 1)
    {
        if (group->keyedElementsInterpolations.size() != (group->keyedElementsIDs.size() - 1) ||
            group->targetKeyedElementsInterpolations.size() != (group->keyedElementsIDs.size() - 1))
        {
            return true;
        }
    }
    for (VNuint i = 0; i < group->keyedElementsInterpolations.size(); i++)
    {
        VNfloat interpolation = group->keyedElementsInterpolations[i];
        VNfloat targetInterpolation = group->targetKeyedElementsInterpolations[i];
        if (!Math::isEqual(interpolation, targetInterpolation, floatDelta))
        {
            return true;
        }
    }
    if (group->position != group->oldPosition ||
        group->rotation != group->oldRotation ||
        group->scale    != group->oldScale)
    {
        return true;
    }
    for (auto keyedElement : group->keyedElementsIDs)
    {
        if (this->shouldKeyedElementBeUpdated(keyedElement, floatDelta))
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldKeyedElementBeUpdated(size_t id, VNfloat floatDelta)
{
    auto foundKeyedElement = this->scene.find(id);
    if (foundKeyedElement == this->scene.end())
    {
        return false;
    }
    if (foundKeyedElement->second->getType() != SvgModel::ModelType::KeyedElement)
    {
        return false;
    }
    Ref<SvgModel::KeyedElement> keyedElement = std::dynamic_pointer_cast<SvgModel::KeyedElement>(foundKeyedElement->second);
    if (keyedElement->keysIDs.empty())
    {
        return false;
    }
    if (this->qualityChanged)
    {
        return true;
    }
    if (keyedElement->transformedVertices.empty() ||
        keyedElement->interpolatedVertices.empty() ||
        keyedElement->transformedBorderMesh == nullptr ||
        keyedElement->borderMesh == nullptr)
    {
        return true;
    }
    if (keyedElement->position != keyedElement->oldPosition ||
        keyedElement->rotation != keyedElement->oldRotation ||
        keyedElement->scale    != keyedElement->oldScale)
    {
        return true;
    }
    if(!Math::isEqual(keyedElement->targetKeyPosition, keyedElement->keyPosition, floatDelta))
    {
        return true;
    }
    for (VNuint i = 0; i < keyedElement->keysPositions.size(); i++)
    {
        if (keyedElement->keysPositions[i] != keyedElement->oldKeysPositions[i])
        {
            return true;
        }
    }
    for (const auto &key : keyedElement->keysIDs)
    {
        if (SvgModelContainer::shouldKeyBeUpdated(key))
        {
            return true;
        }
    }
    return false;
}

bool SvgModelContainer::shouldKeyBeUpdated(size_t id, VNfloat floatDelta)
{
    auto foundElement = this->scene.find(id);
    if (foundElement == this->scene.end())
    {
        return false;
    }
    if (foundElement->second->getType() != SvgModel::ModelType::Key)
    {
        return false;
    }
    Ref<SvgModel::Key> element = std::dynamic_pointer_cast<SvgModel::Key>(foundElement->second);
    if (this->qualityChanged)
    {
        return true;
    }
    if (element->position != element->oldPosition ||
        element->rotation != element->oldRotation ||
        element->scale    != element->oldScale)
    {
        return true;
    }
    if (element->transformedVertices.empty() ||
        element->vertices.empty() ||
        element->transformedBorderMesh == nullptr ||
        element->borderMesh == nullptr)
    {
        return true;
    }
    return false;
}

void SvgModelContainer::updateModel(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    auto foundModel = this->scene.find(id);
    if (foundModel == this->scene.end())
    {
        return;
    }
    if (foundModel->second->getType() != SvgModel::ModelType::Model)
    {
        return;
    }
    Ref<SvgModel::Model> model = std::dynamic_pointer_cast<SvgModel::Model>(foundModel->second);
    for (auto &group : model->groupsIDs)
    {
        if (this->shouldGroupBeUpdated(group, floatDelta))
        {
            this->updateGroup(group, floatDelta, interpolationSpeed);
        }
    }
    if((model->rotation != model->oldRotation) ||
       (model->scale    != model->oldScale))
    {
        model->scaleMatrix = {model->scale.x, 0.0f,
                            0.0f, model->scale.y};
        VNfloat radianRotation = glm::radians(model->rotation);
        model->rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
                                -glm::sin(radianRotation), glm::cos(radianRotation)};
        model->oldRotation = model->rotation;
        model->oldScale    = model->scale;
    }
    if (model->position != model->oldPosition)
    {
        model->oldPosition = model->position;
    }
}

void SvgModelContainer::updateGroup(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    auto foundGroup = this->scene.find(id);
    if (foundGroup == this->scene.end())
    {
        return;
    }
    if (foundGroup->second->getType() != SvgModel::ModelType::Group)
    {
        return;
    }
    Ref<SvgModel::Group> group = std::dynamic_pointer_cast<SvgModel::Group>(foundGroup->second);
    bool keyedElementWasUpdated = false;
    if (group->keyedElementsIDs.empty())
    {
        return;
    }
    for (auto &keyedElement : group->keyedElementsIDs)
    {
        if (this->shouldKeyedElementBeUpdated(keyedElement, floatDelta))
        {
            this->updateKeyedElement(keyedElement, floatDelta, interpolationSpeed);
            keyedElementWasUpdated = true;
        }
    }
    group->keyedElementsInterpolations.resize(group->keyedElementsIDs.size());
    group->targetKeyedElementsInterpolations.resize(group->keyedElementsIDs.size());
    bool shouldDeltasBeUpdated = false;
    for (VNsize i = 0; i < group->keyedElementsInterpolations.size(); i++)
    {
        VNfloat interpolation = group->keyedElementsInterpolations[i];
        VNfloat targetInterpolation = group->targetKeyedElementsInterpolations[i];
        if(!Math::isEqual(interpolation, targetInterpolation, floatDelta))
        {
            shouldDeltasBeUpdated = true;
            break;
        }
    }
    bool transformationChanged = (group->position != group->oldPosition) ||
                                 (group->rotation != group->oldRotation) ||
                                 (group->scale    != group->oldScale);
    if (!(shouldDeltasBeUpdated ||
        keyedElementWasUpdated ||
        group->interpolatedVertices.empty() ||
        group->borderMesh == nullptr ||
        group->transformedBorderMesh == nullptr ||
        transformationChanged))
    {
        return;
    }
    for (VNuint i = 0; i < group->keyedElementsInterpolations.size(); i++)
    {
        VNfloat interpolation = group->keyedElementsInterpolations[i];
        VNfloat targetInterpolation = group->targetKeyedElementsInterpolations[i];
        group->keyedElementsInterpolations[i] = Math::lerpDelta(interpolation, targetInterpolation, interpolationSpeed, floatDelta);
    }

    size_t rootID = group->keyedElementsIDs[0];
    Ref<SvgModel::KeyedElement> rootKeyedElement = std::dynamic_pointer_cast<SvgModel::KeyedElement>(this->scene[rootID]);
    VNsize firstKeyedElementVerticesCount = rootKeyedElement->transformedVertices.size();
    group->interpolatedVertices.resize(firstKeyedElementVerticesCount);

    std::vector<VNfloat> interpolatedValues;
    interpolatedValues.resize(group->keyedElementsIDs.size());

    for (VNuint j = 0; j < firstKeyedElementVerticesCount; j++)
    {
        for (VNuint i = 1; i < group->keyedElementsIDs.size(); i++)
        {
            size_t keyedElementID = group->keyedElementsIDs[i];
            Ref<SvgModel::KeyedElement> keyedElement = std::dynamic_pointer_cast<SvgModel::KeyedElement>(this->scene[keyedElementID]);

            const VNfloat rootFloat = rootKeyedElement->transformedVertices[j];
            const VNfloat targetFloat = keyedElement->transformedVertices[j];

            interpolatedValues[i - 1] = (Math::lerp(rootFloat, targetFloat, group->keyedElementsInterpolations[i - 1]) - rootFloat);
        }
        group->interpolatedVertices[j] = rootKeyedElement->transformedVertices[j];
        for (VNfloat interpolatedValue : interpolatedValues)
        {
            group->interpolatedVertices[j] += interpolatedValue;
        }
    }
    if(group->scale != group->oldScale)
    {
        group->scaleMatrix = {group->scale.x, 0.0f,
                             0.0f, group->scale.y};
        group->oldScale = group->scale;
    }
    if(group->rotation != group->oldRotation)
    {
        VNfloat radianRotation = glm::radians(group->rotation);
        group->rotationMatrix = {glm::cos(radianRotation), glm::sin(radianRotation),
                                -glm::sin(radianRotation), glm::cos(radianRotation)};

        group->oldRotation = group->rotation;

    }
    if (group->position != group->oldPosition)
    {
        group->oldPosition = group->position;
    }

    if (keyedElementWasUpdated)
    {
        group->borderMesh = MeshFactory::fromVertices(group->interpolatedVertices.data(),
                                                     group->interpolatedVertices.size(),
                                                     Mesh::PrimitiveType::Lines);
        SvgModelContainer::transformVertices(group->transformedVertices, group->interpolatedVertices,
                                             group->position,
                                             group->scale,
                                             group->rotation);
        group->transformedBorderMesh = MeshFactory::fromVertices(group->transformedVertices.data(),
                                                                 group->transformedVertices.size(),
                                                                Mesh::PrimitiveType::Lines);
        std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(group->interpolatedVertices);
        group->triangulatedMesh = MeshFactory::fromVerticesIndices(group->interpolatedVertices.data(),
                                                                   group->interpolatedVertices.size(),
                                                                   triangulatedIndices.data(),
                                                                   triangulatedIndices.size(),
                                                                   Mesh::PrimitiveType::Triangles);
    }
}

void SvgModelContainer::updateKeyedElement(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    auto foundKeyedElement = this->scene.find(id);
    if (foundKeyedElement == this->scene.end())
    {
        return;
    }
    if (foundKeyedElement->second->getType() != SvgModel::ModelType::KeyedElement)
    {
        return;
    }
    Ref<SvgModel::KeyedElement> keyedElement = std::dynamic_pointer_cast<SvgModel::KeyedElement>(foundKeyedElement->second);
    bool elementWasUpdated = false;
    if (keyedElement->keysIDs.empty())
    {
        return;
    }
    for (auto &keyID : keyedElement->keysIDs)
    {
        if (this->shouldKeyBeUpdated(keyID, floatDelta))
        {
            this->updateKey(keyID, floatDelta, interpolationSpeed);
            elementWasUpdated = true;
        }
    }
    bool keyChanged = false;
    keyedElement->keysPositions.resize(keyedElement->keysIDs.size());
    keyedElement->oldKeysPositions.resize(keyedElement->keysIDs.size());
    for (VNuint i = 0; i < keyedElement->keysPositions.size(); i++)
    {
        if (keyedElement->keysPositions[i] != keyedElement->oldKeysPositions[i])
        {
            keyChanged = true;
            break;
        }
    }
    bool shouldDeltaBeUpdated = false;
    VNfloat interpolation = keyedElement->keyPosition;
    VNfloat targetInterpolation = keyedElement->targetKeyPosition;
    if (!Math::isEqual(interpolation, targetInterpolation, floatDelta))
    {
        shouldDeltaBeUpdated = true;
    }
    bool transformationChanged = (keyedElement->position != keyedElement->oldPosition) ||
                                 (keyedElement->rotation != keyedElement->oldRotation) ||
                                 (keyedElement->scale    != keyedElement->oldScale);
    if (!(shouldDeltaBeUpdated ||
        elementWasUpdated ||
        keyedElement->transformedVertices.empty() ||
        keyedElement->interpolatedVertices.empty() ||
        keyedElement->borderMesh == nullptr ||
        keyedElement->transformedBorderMesh == nullptr ||
        keyChanged ||
        transformationChanged))
    {
        return;
    }
    if (shouldDeltaBeUpdated)
    {
        keyedElement->keyPosition = Math::lerp(interpolation, targetInterpolation, interpolationSpeed);
    }
    size_t rootElementID = keyedElement->keysIDs[0];
    Ref<SvgModel::Key> rootElement = std::dynamic_pointer_cast<SvgModel::Key>(this->scene[rootElementID]);
    VNuint firstElementVerticesCount = rootElement->transformedVertices.size();
    keyedElement->interpolatedVertices.resize(firstElementVerticesCount);
    keyedElement->transformedVertices.resize(firstElementVerticesCount);

    std::vector<std::pair<VNfloat, VNuint>> sortedKeys;
    sortedKeys.reserve(keyedElement->keysIDs.size());
    for (VNuint index = 0; index < keyedElement->keysPositions.size(); index++)
    {
        VNfloat key = keyedElement->keysPositions[index];
        sortedKeys.emplace_back(key, index);
    }
    std::sort(sortedKeys.begin(), sortedKeys.end(), [](auto &a, auto &b){return a.first < b.first;});
    VNfloat keyPosition = keyedElement->keyPosition;
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

    size_t elementID = keyedElement->keysIDs[keyIndex];
    Ref<SvgModel::Key> key = std::dynamic_pointer_cast<SvgModel::Key>(this->scene[elementID]);
    if (hasNextKey)
    {
        VNfloat interpolationBetweenKeys;
        elementID = keyedElement->keysIDs[nextKeyIndex];
        Ref<SvgModel::Key> nextKey = std::dynamic_pointer_cast<SvgModel::Key>(this->scene[elementID]);
        VNfloat previousKeyPosition = keyedElement->keysPositions[keyIndex];
        VNfloat nextKeyPosition = keyedElement->keysPositions[nextKeyIndex];
        interpolationBetweenKeys = keyPosition - previousKeyPosition;
        interpolationBetweenKeys = interpolationBetweenKeys / (nextKeyPosition - previousKeyPosition);
        keyedElement->interpolatedVertices.resize(key->transformedVertices.size());
        for (VNsize i = 0; i < keyedElement->interpolatedVertices.size(); i++)
        {
            VNfloat prevCoordinate = key->transformedVertices[i];
            VNfloat nextCoordinate = nextKey->transformedVertices[i];
            keyedElement->interpolatedVertices[i] = Math::lerp(prevCoordinate, nextCoordinate, interpolationBetweenKeys);
        }
    }
    else
    {
        keyedElement->interpolatedVertices = key->transformedVertices;
    }
    SvgModelContainer::transformVertices(keyedElement->transformedVertices, keyedElement->interpolatedVertices,
                                         keyedElement->position, keyedElement->scale, keyedElement->rotation);
    keyedElement->oldPosition      = keyedElement->position;
    keyedElement->oldScale         = keyedElement->scale;
    keyedElement->oldRotation      = keyedElement->rotation;
    keyedElement->oldKeysPositions = keyedElement->keysPositions;

    keyedElement->borderMesh = MeshFactory::fromVertices(keyedElement->interpolatedVertices.data(),
                                                        keyedElement->interpolatedVertices.size(),
                                                        Mesh::PrimitiveType::Lines);
    keyedElement->transformedBorderMesh = MeshFactory::fromVertices(keyedElement->transformedVertices.data(),
                                                                   keyedElement->transformedVertices.size(),
                                                                   Mesh::PrimitiveType::Lines);
}

void SvgModelContainer::updateKey(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed)
{
    auto foundElement = this->scene.find(id);
    if (foundElement == this->scene.end())
    {
        return;
    }
    if (foundElement->second->getType() != SvgModel::ModelType::Key)
    {
        return;
    }
    Ref<SvgModel::Key> element = std::dynamic_pointer_cast<SvgModel::Key>(foundElement->second);
    bool transformationChanged = (element->position != element->oldPosition) ||
                                 (element->rotation != element->oldRotation) ||
                                 (element->scale    != element->oldScale);
    if (!(this->qualityChanged ||
          element->transformedVertices.empty() ||
          element->vertices.empty() ||
          element->transformedBorderMesh == nullptr ||
          element->borderMesh == nullptr ||
          transformationChanged))
    {
        return;
    }
    const std::string &documentPath = element->documentPath;
    const std::string &layerName    = element->layerName;
    if (this->svgDocuments.find(documentPath) == this->svgDocuments.end() ||
        this->svgDocuments[documentPath]->getLayerByName(layerName) == nullptr)
    {
        return;
    }
    if (this->qualityChanged ||
        element->vertices.empty())
    {
        Ref<Svg::Document> doc = this->svgDocuments[documentPath];
        const Svg::Layer *layer = doc->getLayerByName(layerName);

        element->vertices = Svg::Rasterizer::rasterize2D(layer, this->quality);
        if (normalizeWithDocumentDimensions)
        {

            Tools::Vertices2D::normalize2DDimensions(element->vertices, doc->getDimensions());
            if (!element->wasLoaded)
            {
                element->position = Tools::Vertices2D::getCenter(element->vertices);
                element->wasLoaded = true;
            }
            Tools::Vertices2D::center2D(element->vertices);
        }
        else
        {
            Tools::Vertices2D::center2D(element->vertices);
            Tools::Vertices2D::normalize2D(element->vertices);
            Tools::Vertices2D::applyVec2Mul(element->vertices, glm::vec2(0.3f));
        }
    }
    SvgModelContainer::transformVertices(element->transformedVertices,
                                         element->vertices,
                                         element->position,
                                         element->scale,
                                         element->rotation);
    element->borderMesh = MeshFactory::fromVertices(element->vertices.data(),
                                                   element->vertices.size(),
                                                   Mesh::PrimitiveType::Lines);
    element->transformedBorderMesh = MeshFactory::fromVertices(element->transformedVertices.data(),
                                                              element->transformedVertices.size(),
                                                              Mesh::PrimitiveType::Lines);
    element->oldPosition = element->position;
    element->oldScale    = element->scale;
    element->oldRotation = element->rotation;
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

void SvgModelContainer::shouldNormalizeWithDocumentDimensions(bool val)
{
    this->normalizeWithDocumentDimensions = val;
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
