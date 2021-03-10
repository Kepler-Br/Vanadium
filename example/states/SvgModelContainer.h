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
        VNfloat interpolation = 0.0f;
        VNfloat targetInterpolation = this->interpolation;
        std::vector<VNfloat> vertices;
    };

    struct Model
    {
        std::vector<ModelElement> elements;
        std::vector<VNfloat> interpolatedVertices;
        std::vector<VNuint> triangulatedIndices;
        Ref<Mesh> triangulatedMesh;
        Ref<Mesh> bordersMesh;
    };

private:
    std::unordered_map<std::string, Ref<Svg::Document>> svgDocuments;
    std::unordered_map<std::string, Model> models;
//    std::set<std::string> modelsToUpdate;

    VNint quality = 10;
    bool qualityChanged = false;

    static bool shouldModelBeUpdated(const Model &model, VNfloat floatDelta = 0.1f);
public:

    void closeDocument(const std::string &documentPath);
    bool openDocument(const std::string &documentPath);
    void setQuality(VNint q);

    void reset();
    void update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta = 0.01f);
//    void scheduleModelUpdate(const std::string &modelName);
    std::unordered_map<std::string, Model> *getModels();
    std::unordered_map<std::string, Ref<Svg::Document>> *getDocuments();
    std::string createModel();
    bool addElementToModel(const std::string &modelName, const std::string &documentPath, const std::string &layerName, bool flipY = false);
    Model *getModelByName(const std::string &modelName);
};

#endif //VANADIUM_SVGMODELCONTAINER_H
