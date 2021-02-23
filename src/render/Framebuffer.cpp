#include "Framebuffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLFramebuffer.h"
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

Framebuffer *FramebufferFactory::create(uint32_t width, uint32_t height)
{

}

}