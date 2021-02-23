#include "RenderApi.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLRenderApi.h"
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

RenderApi *RenderApi::renderApi = nullptr;

RenderApi *RenderApi::instance()
{
    if (RenderApi::renderApi == nullptr)
#if defined(VANADIUM_RENDERAPI_OPENGL)
        RenderApi::renderApi = new OpenGLRenderApi;
#elif defined(VANADIUM_RENDERAPI_OPENGLES)
    #error "OpenGLES is not yet supported."
#elif defined(VANADIUM_RENDERAPI_VULKAN)
    #error "Vulkan is not yet supported."
#elif defined(VANADIUM_RENDERAPI_DIRECTX)
    #error "DirectX is not yet supported."
#elif defined(VANADIUM_RENDERAPI_DIRECTX12)
    #error "DirectX 12 is not yet supported."
#else
    #error "Undefined render api."
#endif
    return RenderApi::renderApi;
}

RenderApi::Api RenderApi::getApi()
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return Api::OpenGL;
#elif defined(VANADIUM_RENDERAPI_OPENGLES)
    #error "OpenGLES is not yet supported."
    return Api::OpenGLES;
#elif defined(VANADIUM_RENDERAPI_VULKAN)
    #error "Vulkan is not yet supported."
    return Api::Vulkan;
#elif defined(VANADIUM_RENDERAPI_DIRECTX)
    #error "DirectX is not yet supported."
    return Api::DirectX;
#elif defined(VANADIUM_RENDERAPI_DIRECTX12)
    #error "DirectX 12 is not yet supported."
    return Api::DirectX12;
#else
    #error "Undefined render api."
#endif
}

}