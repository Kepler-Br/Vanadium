#ifndef VANADIUM_SVGMODELCONTAINER_H
#define VANADIUM_SVGMODELCONTAINER_H

#include "../../src/include/vanadium/Vanadium.h"
#include "SvgModels.h"

using namespace Vanadium;

class SvgModelContainer
{
private:
    std::unordered_map<std::string, Ref<Svg::Document>> svgDocuments;
//    std::unordered_map<std::string, Model> models;
//    std::unordered_map<std::string, Model> patches;
    std::unordered_map<size_t, Ref<SvgModel::Object>> scene;
    std::vector<size_t> modelIDs;
    std::vector<size_t> groupsIDs;
    std::vector<size_t> keyedElementsIDs;
    std::vector<size_t> keyIDs;

    VNint quality = 10;
    bool qualityChanged = false;
    bool normalizeWithDocumentDimensions = true;
    std::string errorString;

    bool shouldModelBeUpdated(size_t id, VNfloat floatDelta = 0.1f);
    bool shouldGroupBeUpdated(size_t id, VNfloat floatDelta = 0.1f);
    bool shouldKeyedElementBeUpdated(size_t id, VNfloat floatDelta = 0.1f);
    bool shouldKeyBeUpdated(size_t id, VNfloat floatDelta = 0.1f);

    void updateModel(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateGroup(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateKeyedElement(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateKey(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);

    static void transformVertices(std::vector<VNfloat> &destination, std::vector<VNfloat> &source, glm::vec2 &position, glm::vec2 &scale, VNfloat rotation);

public:

    void closeDocument(const std::string &documentPath);
    bool openDocument(const std::string &documentPath);
    void setQuality(VNint q);

    void update(VNfloat interpolationSpeed, VNfloat floatInterpolationDelta = 0.01f);
    std::unordered_map<size_t, Ref<SvgModel::Object>> &getScene();
    Ref<SvgModel::Model> getModel(size_t id);
    Ref<SvgModel::Group> getGroup(size_t id);
    Ref<SvgModel::KeyedElement> getKeyedElement(size_t id);
    Ref<SvgModel::Key> getKey(size_t id);
    const std::vector<size_t> &getModelsIDs();
    const std::vector<size_t> &getGroupsIDs();
    const std::vector<size_t> &getKeyedElementsIDs();
    const std::vector<size_t> &getKeysIDs();
    const std::unordered_map<std::string, Ref<Svg::Document>> &getDocuments();
//    Ref<Svg::Document> getDocumentByIndex(VNsize index);
//    std::string getDocumentPathByIndex(VNsize index);
    size_t addModel(const std::string &name = "");
    size_t addGroup(size_t modelID, const std::string &name = "");
    size_t addKeyedElement(size_t groupID, const std::string &name = "");
    size_t addKey(const std::string &documentPath,
                  const std::string &layerName,
                  size_t keyedElementID,
                  const std::string &name = "");

//    Model *getModelByName(const std::string &modelName);
//    Model *getModelByIndex(VNsize index);
//    std::string getModelNameByIndex(VNsize index);
    const std::string &getErrorString();
    void shouldNormalizeWithDocumentDimensions(bool val);

//    static void interpolateModel(Model &model, std::vector<VNfloat> &interpolationTarget, bool interpolateToTarget = false, VNfloat interpolationSpeed = 0.1f);

};

#endif //VANADIUM_SVGMODELCONTAINER_H
