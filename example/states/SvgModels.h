#ifndef VANADIUM_SVGMODELS_H
#define VANADIUM_SVGMODELS_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

namespace SvgModel
{

enum class ModelType
{
    Model = 0,
    Group,
    KeyedElement,
    Key
};

struct Object
{
    virtual ModelType getType() noexcept = 0;
};

struct Key : public Object
{
    ModelType getType() noexcept override
    {
        return ModelType::Key;
    }

    std::string documentPath;
    std::string layerName;
    std::string name;
    size_t id;
    size_t parentID;

    std::vector<VNfloat> vertices;
    std::vector<VNfloat> transformedVertices;
    Ref<Mesh> borderMesh;
    Ref<Mesh> transformedBorderMesh;
    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;

    bool disabled = false;
};

struct KeyedElement : public Object
{
    ModelType getType() noexcept override
    {
        return ModelType::KeyedElement;
    }

    std::string name;
    size_t id;
    size_t parentID;

    VNfloat keyPosition = 0.0f;
    VNfloat targetKeyPosition = this->keyPosition;
    std::vector<VNfloat> interpolatedVertices;
    std::vector<VNfloat> transformedVertices;

    Ref<Mesh> borderMesh;
    Ref<Mesh> transformedBorderMesh;

    std::vector<size_t> keysIDs;
    std::vector<VNfloat> keysPositions;
    std::vector<VNfloat> oldKeysPositions;

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;

    bool disabled = false;
};

struct Group : public Object
{
    ModelType getType() noexcept override
    {
        return ModelType::Group;
    }

    std::string name;
    size_t id;
    size_t parentID;

    std::vector<size_t> keyedElementsIDs;
    std::vector<VNfloat> interpolatedVertices;
    std::vector<VNfloat> transformedVertices;

    Ref<Mesh> borderMesh;
    Ref<Mesh> transformedBorderMesh;
    Ref<Mesh> triangulatedMesh;

    glm::vec3 auraColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 wireframeColor = glm::vec4(1.0f);
    glm::vec3 bodyColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat2 scaleMatrix = glm::mat2(1.0f);
    glm::mat2 rotationMatrix = glm::mat2(1.0f);

    bool drawAsWireframe = false;
    bool disabled = false;
    bool isPatch = false;
    bool affectAura = false;
    bool affectBodyColor = true;

    std::vector<VNfloat> keyedElementsInterpolations;
    std::vector<VNfloat> targetKeyedElementsInterpolations;

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;
    VNint drawLayer = 1;
};

struct Model : public Object
{
    ModelType getType() noexcept override
    {
        return ModelType::Model;
    }

    std::string name;
    size_t id;
    std::vector<size_t> groupsIDs;

    glm::mat2 scaleMatrix = glm::mat2(1.0f);
    glm::mat2 rotationMatrix = glm::mat2(1.0f);

    bool drawAsWireframe = false;
    bool disabled = false;

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;
};

}

#endif //VANADIUM_SVGMODELS_H
