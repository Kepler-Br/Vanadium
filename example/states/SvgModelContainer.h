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
    const VNint totalLayers = 21;

    bool shouldModelBeUpdated(size_t id, VNfloat floatDelta = 0.1f);
    bool shouldGroupBeUpdated(size_t id, VNfloat floatDelta = 0.1f);
    bool shouldKeyedElementBeUpdated(size_t id, VNfloat floatDelta = 0.1f);
    bool shouldKeyBeUpdated(size_t id, VNfloat floatDelta = 0.1f);

    void updateModel(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateGroup(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateKeyedElement(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);
    void updateKey(size_t id, VNfloat floatDelta, VNfloat interpolationSpeed);

    void propagateDeltas(size_t id);
//    void propagateDeltasFromModel(size_t id, const glm::vec2 &deltaScale, const glm::vec2 &deltaPosition);
    void propagateDeltasFromGroup(size_t id);
    void propagateDeltasFromKeyedElement(size_t id);

    static void transformVertices(std::vector<VNfloat> &destination, std::vector<VNfloat> &source, const glm::vec2 &position, const glm::vec2 &scale, VNfloat rotation);
    static void transformVerticesLocal(std::vector<VNfloat> &destination, std::vector<VNfloat> &source, const glm::vec2 &position, const glm::vec2 &localPosition, const glm::vec2 &scale, VNfloat rotation);

    void removeModel(size_t id);
    void removeGroup(size_t id);
    void removeKeyedElement(size_t id);
    void removeKey(size_t id);

    void duplicateModel(size_t id);
    void duplicateGroup(size_t id, size_t parentID = 0);
    void duplicateKeyedElement(size_t id, size_t parentID = 0);
    void duplicateKey(size_t id, size_t parentID = 0);

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
    Ref<SvgModel::Object> getObject(size_t id);

    const std::vector<size_t> &getModelsIDs();
    const std::vector<size_t> &getGroupsIDs();
    const std::vector<size_t> &getKeyedElementsIDs();
    const std::vector<size_t> &getKeysIDs();

    const std::unordered_map<std::string, Ref<Svg::Document>> &getDocuments();
    Ref<Svg::Document> getDocumentByPath(const std::string &path);
    bool isLayerAvailable(const std::string &documentPath, const std::string &layerName);

    SvgModel::ModelType getType(size_t id);
    void centerObjectToChildren(size_t id);

    size_t addModel(const std::string &name = "");
    size_t addGroup(size_t modelID, const std::string &name = "");
    size_t addKeyedElement(size_t groupID, const std::string &name = "");
    size_t addKey(size_t keyedElementID,
                  const std::string &documentPath = "",
                  const std::string &layerName = "",
                  const std::string &name = "");
    void removeFromScene(size_t id);
    void duplicate(size_t id);
    VNint getTotalLayers();

    const std::string &getErrorString();
    void shouldNormalizeWithDocumentDimensions(bool val);


};

#endif //VANADIUM_SVGMODELCONTAINER_H
