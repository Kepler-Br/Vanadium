#ifndef VANADIUM_SVGMODELCONTAINER_H
#define VANADIUM_SVGMODELCONTAINER_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

class SvgModelContainer
{
public:
    struct ModelElement
    {
        std::string documentName;
        std::string layerName;
        std::string name;
        VNfloat interpolation = 0.0f;
        VNfloat targetInterpolation = this->interpolation;
        std::vector<VNfloat> vertices;
        std::vector<VNfloat> transformedVertices;
        Ref<Mesh> borderMesh;
        Ref<Mesh> transformedBorderMesh;
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        VNfloat rotation = 0.0f;
        std::vector<ModelElement> intermediateElements;

        glm::vec2 oldPosition = this->position;
        glm::vec2 oldScale = this->scale;
        VNfloat oldRotation = this->rotation;
    };

    struct Model
    {
        std::vector<ModelElement> elements;
        std::vector<VNfloat> interpolatedVertices;
        std::vector<VNuint> triangulatedIndices;
        Ref<Mesh> triangulatedMesh;
        Ref<Mesh> borderMesh;
    };

private:
    std::unordered_map<std::string, Ref<Svg::Document>> svgDocuments;
    std::unordered_map<std::string, Model> models;

    VNint quality = 10;
    bool shouldReinitElements = false;
    std::string errorString;

    static bool shouldModelBeUpdated(const Model &model, VNfloat floatDelta = 0.1f);
    static bool shouldElementBeUpdated(const ModelElement &element);

public:

    void closeDocument(const std::string &documentPath);
    bool openDocument(const std::string &documentPath);
    void setQuality(VNint q);

    void reset();
    void update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta = 0.01f);
//    void scheduleModelUpdate(const std::string &modelName);
    std::unordered_map<std::string, Model> &getModels();
    std::unordered_map<std::string, Ref<Svg::Document>> &getDocuments();
    Ref<Svg::Document> getDocumentByIndex(VNsize index);
    std::string getDocumentPathByIndex(VNsize index);
    std::string createModel();
    bool addElementToModel(const std::string &modelName, const std::string &documentPath, const std::string &layerName, bool flipY = false);
    bool addIntermediateElementToElement(const std::string &modelName, const std::string &documentPath, const std::string &layerName, VNuint elementID);
    Model *getModelByName(const std::string &modelName);
    Model *getModelByIndex(VNsize index);
    std::string getModelNameByIndex(VNsize index);
    const std::string &getErrorString();

    static void interpolateModel(Model &model, std::vector<VNfloat> &interpolationTarget, bool interpolateToTarget = false, VNfloat interpolationSpeed = 0.1f);
    static void updateElementTransformations(ModelElement &element);
    static glm::vec2 getElementBoundingBox(const ModelElement &element);
    static glm::vec2 getModelBoundingBox(const Model &model);


};

#endif //VANADIUM_SVGMODELCONTAINER_H
