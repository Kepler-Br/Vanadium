#include "Framebuffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLFramebuffer.h"
    using FramebufferImpl = Vanadium::OpenGLFramebuffer;
#endif

namespace Vanadium
{

Ref<Framebuffer> FramebufferFactory::create(const Framebuffer::Specification &specification, Texture::Filtering filtering)
{
    return MakeRef<FramebufferImpl>(specification, filtering);
}

}