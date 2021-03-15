#ifndef VANADIUM_SVGMODELS_H
#define VANADIUM_SVGMODELS_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

namespace SvgModel
{

enum class ModelType
{
    None = 0,
    Model,
    Group,
    KeyedElement,
    Key
};

struct Object
{
    virtual ModelType getType() noexcept = 0;
    virtual bool isDisabled() noexcept = 0;
    virtual void setDisabled(bool val) noexcept  = 0;
    virtual const std::string &getName() noexcept = 0;
    virtual void setName(const std::string &newName) noexcept = 0;
    virtual size_t getID() noexcept = 0;
};

struct Key : public Object
{
    ModelType getType() noexcept override
    {
        return ModelType::Key;
    }

    bool isDisabled() noexcept override
    {
        return this->disabled;
    }

    void setDisabled(bool val) noexcept override
    {
        this->disabled = val;
    }

    const std::string &getName() noexcept override
    {
        return this->name;
    }

    void setName(const std::string &newName) noexcept override
    {
        if (!name.empty())
        {
            this->name = newName;
        }
    }

    size_t getID() noexcept override
    {
        return id;
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
    bool wasLoaded = false;
};

struct KeyedElement : public Object
{
    ModelType getType() noexcept override
    {
        return ModelType::KeyedElement;
    }

    bool isDisabled() noexcept override
    {
        return this->disabled;
    }

    void setDisabled(bool val) noexcept override
    {
        this->disabled = val;
    }

    const std::string &getName() noexcept override
    {
        return this->name;
    }

    void setName(const std::string &newName) noexcept override
    {
        if (!name.empty())
        {
            this->name = newName;
        }
    }

    size_t getID() noexcept override
    {
        return id;
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

    bool isDisabled() noexcept override
    {
        return this->disabled;
    }

    void setDisabled(bool val) noexcept override
    {
        this->disabled = val;
    }

    const std::string &getName() noexcept override
    {
        return this->name;
    }

    void setName(const std::string &newName) noexcept override
    {
        if (!name.empty())
        {
            this->name = newName;
        }
    }

    size_t getID() noexcept override
    {
        return id;
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

    bool isDisabled() noexcept override
    {
        return this->disabled;
    }

    void setDisabled(bool val) noexcept override
    {
        this->disabled = val;
    }

    const std::string &getName() noexcept override
    {
        return this->name;
    }

    void setName(const std::string &newName) noexcept override
    {
        if (!name.empty())
        {
            this->name = newName;
        }
    }

    size_t getID() noexcept override
    {
        return id;
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
