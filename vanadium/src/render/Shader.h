#ifndef VANADIUM_SHADER_H
#define VANADIUM_SHADER_H

#include <string>
#include <unordered_map>

#include <tinyxml2.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>

#include "../core/Types.h"
#include "RenderApi.h"

namespace Vanadium
{

class Shader
{
public:

    enum class Type
    {
        Unknown = 0,
        Vertex,
        Pixel,
        Geometry,
        Compute,
        TesselationControl,
        TesselationEval,
    };

    using ShaderMap = std::unordered_map<Shader::Type, std::string>;

    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;

    virtual uint32_t getGlobalId(const std::string &name) noexcept = 0;

    virtual void *getRaw() const noexcept = 0;

    virtual void setGlobalFloat(const std::string &name, VNfloat value) = 0;
    virtual void setGlobalFloat2(const std::string &name, const glm::vec2 &value) = 0;
    virtual void setGlobalFloat3(const std::string &name, const glm::vec3 &value) = 0;
    virtual void setGlobalFloat4(const std::string &name, const glm::vec4 &value) = 0;
    virtual void setGlobalInt(const std::string &name, VNint value) = 0;
    virtual void setGlobalMat3(const std::string &name, const glm::mat3 &value) = 0;
    virtual void setGlobalMat4(const std::string &name, const glm::mat4 &value) = 0;

    virtual const std::string &getName() const noexcept = 0;

    static std::string typeToString(Shader::Type shaderType);
    static Shader::Type stringToType(const std::string &typeName);

};

class ShaderFactory
{
    using ShaderMap = std::unordered_map<Shader::Type, std::string>;

private:
    static ShaderMap parseShaderAsset(const std::string &asset);

public:
    static Ref<Shader> create(const std::string &assetPath, const std::string &name = "Untitled shader");
//    static Ref<Shader> create(const std::string &vertex, const std::string &fragment, const std::string &name = "Untitled shader");

};

}

#endif //VANADIUM_SHADER_H
