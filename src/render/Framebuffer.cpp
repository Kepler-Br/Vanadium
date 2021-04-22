#include "render/Framebuffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "platform/opengl/OpenGLFramebuffer.h"
using FramebufferImpl = Vanadium::OpenGLFramebuffer;
#endif

namespace Vanadium {

Ref<Framebuffer> FramebufferFactory::create(
    const Framebuffer::Specification &specification) {
  return MakeRef<FramebufferImpl>(specification);
}

}  // namespace Vanadium