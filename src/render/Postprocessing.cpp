#include "render/Postprocessing.h"

#include "render/Shader.h"
#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "platform/opengl/OpenGLPostprocessing.h"
using PostprocessingImpl = Vanadium::OpenGLPostprocessing;
#endif

namespace Vanadium {

Ref<Postprocessing> PostprocessingFactory::create(const Ref<Shader> &shader,
                                                  VNuint width, VNuint height) {
  return MakeRef<PostprocessingImpl>(shader, width, height);
}

Ref<Postprocessing> PostprocessingFactory::create(
    const Ref<Shader> &shader, const Framebuffer::Specification &specs) {
  return MakeRef<PostprocessingImpl>(shader, specs);
}

}  // namespace Vanadium