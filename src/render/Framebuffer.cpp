#include "Framebuffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLFramebuffer.h"
#endif

namespace Vanadium
{

Ref<Framebuffer> FramebufferFactory::create(const Framebuffer::Specification &specification)
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return MakeRef<OpenGLFramebuffer>(specification);
#else
    #error "Unsupported render API."
#endif
}

}