#include "Shader.h"
#include "../core/exceptions/ShaderCompilationError.h"

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

std::unordered_map<std::string, std::string> Shader::loadShaderAsset(const std::string &path)
{

}

Shader *Shader::create(const std::string &assetPath)
{
    Shader *shader;


    try
    {
        #if defined(VANADIUM_RENDERAPI_OPENGL)
//            shader = new OpenGLShader();
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
        VAN_ENGINE_ERROR("Shader throws \"{}\" during compilation.", e.what());
        return nullptr;
    }
    return shader;
}

Shader *Shader::create(const std::string &vertex, const std::string &fragment)
{
    return nullptr;
}

}