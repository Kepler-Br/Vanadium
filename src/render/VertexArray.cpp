#include "render/VertexArray.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "platform/opengl/OpenGLVertexArray.h"
using VertexArrayImpl = Vanadium::OpenGLVertexArray;
#endif

namespace Vanadium {

Ref<VertexArray> VertexArrayFactory::create() {
  //    VAN_ENGINE_TRACE("Creating VertexArray.");
  return MakeRef<VertexArrayImpl>();
}

}  // namespace Vanadium