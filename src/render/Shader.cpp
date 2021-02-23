#include "Shader.h"
#include "../core/exceptions/ShaderCompilationError.h"
#include "../core/Log.h"
#include "RenderApi.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLShader.h"
#elif defined(VANADIUM_RENDERAPI_OPENGLES)
    #error "Unsupported render api."
#elif defined(VANADIUM_RENDERAPI_VULKAN)
    #error "Unsupported render api."
#elif defined(VANADIUM_RENDERAPI_DIRECTX)
    #error "Unsupported render api."
#elif defined(VANADIUM_RENDERAPI_DIRECTX12)
    #error "Unsupported render api."
#else
    #error "Undefined render api."
#endif

namespace Vanadium
{

std::string Shader::typeToString(Shader::Type shaderType)
{
    switch (shaderType)
    {
        case Shader::Type::Pixel:
            return std::string("Pixel");
        case Shader::Type::Vertex:
            return std::string("Vertex");
        default:
            return std::string("Unknown");
    }
}

/*
 * ShaderFactory
 */

using ShaderMap = std::unordered_map<Shader::Type, std::string>;

ShaderMap ShaderFactory::extractShadersFromYamlNode(const YAML::Node &yamlNode)
{
    ShaderMap shaders;

    if (!yamlNode)
    {
        VAN_ENGINE_ERROR("Shader asset has no shader type for selected render platform.");
        return shaders;
    }
    if (yamlNode.size() < 2 || !yamlNode["vertex"] || !yamlNode["pixel"])
    {
        VAN_ENGINE_ERROR("Shader asset has insufficient programs "
                         "for selected render platform(Vertex and pixel are required).");
        return shaders;
    }
    for (auto node : yamlNode)
    {
        std::string nodeName = node.first.as<std::string>();
        if (nodeName == "vertex")
            shaders[Shader::Type::Vertex] = node.second.as<std::string>();
        else if (nodeName == "pixel")
            shaders[Shader::Type::Pixel] = node.second.as<std::string>();
        else
            VAN_ENGINE_INFO("Unknown shader program type: \"{}\".", nodeName);
    }
    return shaders;
}

ShaderMap ShaderFactory::loadShaderAsset(const std::string &path)
{
    ShaderMap shaders;
    YAML::Node shaderAsset;

    VAN_ENGINE_TRACE("Loading shader asset: {}", path);
    RenderApi::Api currentApi = RenderApi::getApi();
    try
    {
        shaderAsset = YAML::LoadFile(path);
    }
    catch (const YAML::BadFile &e)
    {
        VAN_ENGINE_ERROR("Cannot load shader asset file: {}", path);
        return shaders;
    }
    catch (const YAML::ParserException &e)
    {
        VAN_ENGINE_ERROR("Invalid shader asset file: {}", path);
        return shaders;
    }
    switch (currentApi)
    {
        case RenderApi::Api::OpenGL:
            shaders = ShaderFactory::extractShadersFromYamlNode(shaderAsset["OpenGL"]);
            break;
        default:
            VAN_ENGINE_ERROR("Not supported render API.");
    }
    return shaders;
}


Shader *ShaderFactory::create(const std::string &assetPath, const std::string &name)
{
    Shader *shader;
    ShaderMap shaderSources = ShaderFactory::loadShaderAsset(assetPath);

    if (shaderSources.empty())
        return nullptr;
    try
    {
    #if defined(VANADIUM_RENDERAPI_OPENGL)
        shader = new OpenGLShader(name, shaderSources);
    #elif defined(VANADIUM_RENDERAPI_OPENGLES)
        #error "Unsupported render api."
    #elif defined(VANADIUM_RENDERAPI_VULKAN)
        #error "Unsupported render api."
    #elif defined(VANADIUM_RENDERAPI_DIRECTX)
        #error "Unsupported render api."
    #elif defined(VANADIUM_RENDERAPI_DIRECTX12)
        #error "Unsupported render api."
    #else
        #error "Undefined render api."
    #endif
    }
    catch (const ShaderCompilationError &e)
    {
        VAN_ENGINE_ERROR("Shader \"{}\" throws \"{}\" during compilation.", name, e.what());
        return nullptr;
    }
    return shader;
}

Shader *ShaderFactory::create(const std::string &vertex, const std::string &fragment, const std::string &name)
{
    Shader *shader;
    ShaderMap shaderSources({
                        {Shader::Type::Vertex, vertex},
                        {Shader::Type::Pixel, fragment}
                    });

    try
    {
    #if defined(VANADIUM_RENDERAPI_OPENGL)
        shader = new OpenGLShader(name, shaderSources);
    #elif defined(VANADIUM_RENDERAPI_OPENGLES)
        #error "Unsupported render api."
    #elif defined(VANADIUM_RENDERAPI_VULKAN)
        #error "Unsupported render api."
    #elif defined(VANADIUM_RENDERAPI_DIRECTX)
        #error "Unsupported render api."
    #elif defined(VANADIUM_RENDERAPI_DIRECTX12)
        #error "Unsupported render api."
    #else
        #error "Undefined render api."
    #endif
    }
    catch (const ShaderCompilationError &e)
    {
        VAN_ENGINE_ERROR("Shader \"{}\" throws \"{}\" during compilation.", name, e.what());
        return nullptr;
    }
    return shader;
}

}