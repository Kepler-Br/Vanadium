#include "render/IndexBuffer.h"

#include <vector>
#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "platform/opengl/OpenGLIndexBuffer.h"
using IndexBufferImpl = Vanadium::OpenGLIndexBuffer;
#endif

namespace Vanadium {

Ref<IndexBuffer> IndexBufferFactory::create(const std::vector<VNuint> &data) {
  return IndexBufferFactory::create(&data[0], data.size());
}

Ref<IndexBuffer> IndexBufferFactory::create(const VNuint *data, VNsize count) {
  return MakeRef<IndexBufferImpl>(data, count);
}

}  // namespace Vanadium