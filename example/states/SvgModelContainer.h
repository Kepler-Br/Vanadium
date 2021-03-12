#ifndef VANADIUM_SVGMODELCONTAINER_H
#define VANADIUM_SVGMODELCONTAINER_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

class SvgModelContainer
{
public:
    struct Element
    {
        std::string documentPath;
        std::string layerName;
        std::string name;
//        VNfloat interpolation = 0.0f;
//        VNfloat targetInterpolation = this->interpolation;
        std::vector<VNfloat> vertices;
        std::vector<VNfloat> transformedVertices;
        Ref<Mesh> borderMesh;
        Ref<Mesh> transformedBorderMesh;
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        VNfloat rotation = 0.0f;
//        std::vector<ModelElement> intermediateElements;

        glm::vec2 oldPosition = this->position;
        glm::vec2 oldScale = this->scale;
        VNfloat oldRotation = this->rotation;
    };

    struct KeyedElement
    {
        std::string name;
        VNfloat keyPosition = 0.0f;
        VNfloat targetKeyPosition = this->keyPosition;
        std::vector<VNfloat> interpolatedVertices;
        std::vector<VNfloat> transformedVertices;
        Ref<Mesh> borderMesh;
        Ref<Mesh> transformedBorderMesh;
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        VNfloat rotation = 0.0f;
        std::vector<Element> keys;
        std::vector<VNfloat> keysPositions;
        std::vector<VNfloat> oldKeysPositions;

        glm::vec2 oldPosition = this->position;
        glm::vec2 oldScale = this->scale;
        VNfloat oldRotation = this->rotation;
    };

    struct Group
    {
        std::string name;
        std::vector<KeyedElement> keyedElements;
        std::vector<VNfloat> interpolatedVertices;
        std::vector<VNfloat> transformedVertices;

        Ref<Mesh> borderMesh;
        Ref<Mesh> transformedBorderMesh;

        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        VNfloat rotation = 0.0f;
//        VNfloat keyPosition = 0.0f;
//        VNfloat targetKeyPosition = this->keyPosition;
        std::vector<VNfloat> keyedElementsInterpolations;
        std::vector<VNfloat> targetKeyedElementsInterpolations;

        glm::vec2 oldPosition = this->position;
        glm::vec2 oldScale = this->scale;
        VNfloat oldRotation = this->rotation;
    };

    struct Model
    {
        std::string name;
        std::vector<Group> groups;
        std::vector<VNfloat> interpolatedVertices;
        std::vector<VNuint> triangulatedIndices;
        Ref<Mesh> triangulatedMesh;
        Ref<Mesh> borderMesh;

        std::vector<VNfloat> groupInterpolations;
        std::vector<VNfloat> targetGroupInterpolations;

        glm::mat2 transformationMatrix = glm::mat4(1.0f);

        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        VNfloat rotation = 0.0f;

        glm::vec2 oldPosition = this->position;
        glm::vec2 oldScale = this->scale;
        VNfloat oldRotation = this->rotation;
    };

private:
    std::unordered_map<std::string, Ref<Svg::Document>> svgDocuments;
    std::unordered_map<std::string, Model> models;

    VNint quality = 10;
    bool shouldReinitElements = false;
    std::string errorString;

    bool shouldModelBeUpdated(const Model &model, VNfloat floatDelta = 0.1f);
    bool shouldGroupBeUpdated(const Group &group, VNfloat floatDelta = 0.1f);
    bool shouldKeyedElementBeUpdated(const KeyedElement &keyedElement, VNfloat floatDelta = 0.1f);
    bool shouldElementBeUpdated(const Element &element, VNfloat floatDelta = 0.1f);

    void updateModel(Model &model, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateGroup(Group &group, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateKeyedElement(KeyedElement &keyedElement, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateElement(Element &element, VNfloat floatDelta, VNfloat interpolationSpeed);

    static void transformVertices(std::vector<VNfloat> &destination, std::vector<VNfloat> &source, glm::vec2 &position, glm::vec2 &scale, VNfloat rotation);

public:

    void closeDocument(const std::string &documentPath);
    bool openDocument(const std::string &documentPath);
    void setQuality(VNint q);

    void reset();
    void update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta = 0.01f);
    std::unordered_map<std::string, Model> &getModels();
    std::unordered_map<std::string, Ref<Svg::Document>> &getDocuments();
    Ref<Svg::Document> getDocumentByIndex(VNsize index);
    std::string getDocumentPathByIndex(VNsize index);
    bool createModel(const std::string &modelName);
    bool addGroupToModel(const std::string &modelName, const std::string &groupName);
    bool addKeyedElementToGroup(const std::string &modelName, const std::string &keyedElementName, VNuint groupIndex);
    bool addElementToKeyedElement(const std::string &modelName, const std::string &elementName,
                                  const std::string &documentPath, const std::string &layerName,
                                  VNuint groupIndex, VNuint keyedElementIndex);
//    bool addElementToGroup(const std::string &modelName, const std::string &documentPath, const std::string &layerName, VNuint groupIndex);
//    bool addIntermediateElementToElement(const std::string &modelName, const std::string &documentPath,
//                                         const std::string &layerName, VNuint groupID, VNuint elementID);

    Model *getModelByName(const std::string &modelName);
    Model *getModelByIndex(VNsize index);
    std::string getModelNameByIndex(VNsize index);
    const std::string &getErrorString();

    static void interpolateModel(Model &model, std::vector<VNfloat> &interpolationTarget, bool interpolateToTarget = false, VNfloat interpolationSpeed = 0.1f);

};

#endif //VANADIUM_SVGMODELCONTAINER_H
