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
    virtual glm::vec2 getPosition() noexcept = 0;
    virtual void setPosition(const glm::vec2 &newPosition) noexcept = 0;
    virtual glm::vec2 getScale() noexcept = 0;
    virtual void setScale(const glm::vec2 &newScale) noexcept = 0;
    virtual VNfloat getRotation() noexcept = 0;
    virtual void setRotation(VNfloat newRotation) noexcept = 0;
    virtual size_t getParentID() noexcept = 0;
    virtual void setParentID(size_t newParentID) noexcept = 0;
    virtual void update(VNfloat interpolationSpeed) noexcept = 0;
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

    glm::vec2 getPosition() noexcept override
    {
        return this->position;
    }

    void setPosition(const glm::vec2 &newPosition) noexcept override
    {
        this->position = newPosition;
    }

    glm::vec2 getScale() noexcept override
    {
        return this->scale;
    }

    void setScale(const glm::vec2 &newScale) noexcept override
    {
        this->scale = newScale;
    }

    VNfloat getRotation() noexcept override
    {
        return this->rotation;
    }

    void setRotation(VNfloat newRotation) noexcept override
    {
        this->rotation = newRotation;
    }

    size_t getParentID() noexcept override
    {
        return this->parentID;
    }

    void setParentID(size_t newParentID) noexcept override
    {
        if (newParentID == 0)
        {
            return;
        }
        this->parentID = newParentID;
    }

    bool stateChanged = false;

    void setDocumentPath(const std::string &newPath)
    {
        this->documentPath = newPath;
        this->stateChanged = true;
    }

    void setLayerName(const std::string &newLayer)
    {
        this->layerName = newLayer;
        this->stateChanged = true;
    }

    void update(VNfloat interpolationSpeed) noexcept override
    {
        this->wasDisabled = this->disabled;
    }

    std::string documentPath;
    std::string layerName;
    std::string name;
    size_t id;
    size_t parentID;

    std::vector<VNfloat> vertices;
//    std::vector<VNfloat> transformedVertices;
    Ref<Mesh> borderMesh;
//    Ref<Mesh> transformedBorderMesh;

    glm::mat2 scaleMatrix = glm::mat2(1.0f);
    glm::mat2 rotationMatrix = glm::mat2(1.0f);

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;

    glm::vec2 scaledPosition = this->position;
    glm::vec2 oldScaledPosition = this->scaledPosition;

    glm::vec2 rotatedPosition = this->position;
    glm::vec2 oldRotatedPosition = this->rotatedPosition;

    bool disabled = false;
    bool wasDisabled = this->disabled;
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

    glm::vec2 getPosition() noexcept override
    {
        return this->position;
    }

    void setPosition(const glm::vec2 &newPosition) noexcept override
    {
        this->position = newPosition;
    }

    glm::vec2 getScale() noexcept override
    {
        return this->scale;
    }

    void setScale(const glm::vec2 &newScale) noexcept override
    {
        this->scale = newScale;
    }

    VNfloat getRotation() noexcept override
    {
        return this->rotation;
    }

    void setRotation(VNfloat newRotation) noexcept override
    {
        this->rotation = newRotation;
    }

    size_t getParentID() noexcept override
    {
        return this->parentID;
    }

    void setParentID(size_t newParentID) noexcept override
    {
        if (newParentID == 0)
        {
            return;
        }
        this->parentID = newParentID;
    }

    bool stateChanged = false;

    void addChild(size_t childID)
    {
        if (childID == 0)
        {
            return;
        }
        this->stateChanged = true;
        this->keysIDs.push_back(childID);
    }

    void removeChild(size_t childID)
    {
        auto found = std::find(this->keysIDs.begin(), this->keysIDs.end(), childID);
        if (found == this->keysIDs.end())
        {
            return;
        }
        this->keysIDs.erase(found);
        this->stateChanged = true;
    }

    void update(VNfloat interpolationSpeed) noexcept override
    {
        this->wasDisabled = this->disabled;
        if (this->sinusInterpolationUpdate)
        {
            if (this->sinusInterpolationForwardUpdate)
            {
                this->targetKeyPosition += glm::sin(interpolationSpeed/40.0f);
                if (this->targetKeyPosition > 1.0f)
                {
                    this->targetKeyPosition = 1.0f;
                    sinusInterpolationForwardUpdate = false;
                }
            }
            else if (!this->sinusInterpolationForwardUpdate)
            {
                this->targetKeyPosition -= glm::sin(interpolationSpeed/40.0f);
                if (this->targetKeyPosition < 0.0f)
                {
                    this->targetKeyPosition = 0.0f;
                    sinusInterpolationForwardUpdate = true;
                }
            }
        }
    }

    std::string name;
    size_t id;
    size_t parentID;

    VNfloat keyPosition = 0.0f;
    VNfloat targetKeyPosition = this->keyPosition;
    std::vector<VNfloat> interpolatedVertices;
//    std::vector<VNfloat> transformedVertices;

    Ref<Mesh> borderMesh;
//    Ref<Mesh> transformedBorderMesh;

    std::vector<size_t> keysIDs;
    std::vector<VNfloat> keysPositions;
    std::vector<VNfloat> oldKeysPositions;

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

//    glm::vec2 averagePosition = this->position;
//    glm::vec2 averageScale = this->scale;
//    VNfloat averageRotation = this->rotation;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;

    glm::vec2 scaledPosition = this->position;
    glm::vec2 oldScaledPosition = this->scaledPosition;

    glm::mat2 scaleMatrix = glm::mat2(1.0f);
    glm::mat2 rotationMatrix = glm::mat2(1.0f);

    bool disabled = false;
    bool wasDisabled = this->disabled;

    bool sinusInterpolationUpdate = false;
    bool sinusInterpolationForwardUpdate = true;
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

    glm::vec2 getPosition() noexcept override
    {
        return this->position;
    }

    void setPosition(const glm::vec2 &newPosition) noexcept override
    {
        this->position = newPosition;
    }

    glm::vec2 getScale() noexcept override
    {
        return this->scale;
    }

    void setScale(const glm::vec2 &newScale) noexcept override
    {
        this->scale = newScale;
    }

    VNfloat getRotation() noexcept override
    {
        return this->rotation;
    }

    void setRotation(VNfloat newRotation) noexcept override
    {
        this->rotation = newRotation;
    }

    size_t getParentID() noexcept override
    {
        return this->parentID;
    }

    void setParentID(size_t newParentID) noexcept override
    {
        if (newParentID == 0)
        {
            return;
        }
        this->parentID = newParentID;
    }

    bool stateChanged = false;

    void addChild(size_t childID)
    {
        if (childID == 0)
        {
            return;
        }
        this->stateChanged = true;
        this->keyedElementsIDs.push_back(childID);
    }

    void removeChild(size_t childID)
    {
        auto found = std::find(this->keyedElementsIDs.begin(), this->keyedElementsIDs.end(), childID);
        if (found == this->keyedElementsIDs.end())
        {
            return;
        }
        this->keyedElementsIDs.erase(found);
        this->stateChanged = true;
    }

    void update(VNfloat interpolationSpeed) noexcept override
    {
        this->wasDisabled = this->disabled;
    }

    std::string name;
    size_t id;
    size_t parentID;

    std::vector<size_t> keyedElementsIDs;
    std::vector<VNfloat> interpolatedVertices;
//    std::vector<VNfloat> transformedVertices;

    Ref<Mesh> borderMesh;
//    Ref<Mesh> transformedBorderMesh;
    Ref<Mesh> triangulatedMesh;

    glm::vec3 auraColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec3 wireframeColor = glm::vec4(1.0f);
    glm::vec3 bodyColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat2 scaleMatrix = glm::mat2(1.0f);
    glm::mat2 rotationMatrix = glm::mat2(1.0f);

    bool drawAsWireframe = false;
    bool disabled = false;
    bool wasDisabled = this->disabled;
    bool isPatch = false;
    bool affectAura = false;
    bool affectBodyColor = true;

    std::vector<VNfloat> keyedElementsInterpolations;
    std::vector<VNfloat> targetKeyedElementsInterpolations;

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    VNfloat rotation = 0.0f;

    glm::vec2 globalPosition = this->position;

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

    glm::vec2 getPosition() noexcept override
    {
        return this->position;
    }

    void setPosition(const glm::vec2 &newPosition) noexcept override
    {
        this->position = newPosition;
    }

    glm::vec2 getScale() noexcept override
    {
        return this->scale;
    }

    void setScale(const glm::vec2 &newScale) noexcept override
    {
        this->scale = newScale;
    }

    VNfloat getRotation() noexcept override
    {
        return this->rotation;
    }

    void setRotation(VNfloat newRotation) noexcept override
    {
        this->rotation = newRotation;
    }

    size_t getParentID() noexcept override
    {
        return 0;
    }

    void setParentID(size_t newParentID) noexcept override
    {}

    bool stateChanged = false;

    void addChild(size_t childID)
    {
        if (childID == 0)
        {
            return;
        }
        this->stateChanged = true;
        this->groupsIDs.push_back(childID);
    }

    void removeChild(size_t childID)
    {
        auto found = std::find(this->groupsIDs.begin(), this->groupsIDs.end(), childID);
        if (found == this->groupsIDs.end())
        {
            return;
        }
        this->groupsIDs.erase(found);
        this->stateChanged = true;
    }

    void update(VNfloat interpolationSpeed) noexcept override
    {}

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

    glm::vec2 globalPosition = this->position;

    glm::vec2 oldPosition = this->position;
    glm::vec2 oldScale = this->scale;
    VNfloat oldRotation = this->rotation;
};

}

#endif //VANADIUM_SVGMODELS_H
