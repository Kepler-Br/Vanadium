#ifndef VANADIUM_OPENGLINDEXBUFFER_H
#define VANADIUM_OPENGLINDEXBUFFER_H

#include "../../core/Types.h"
#include "../../render/IndexBuffer.h"

namespace Vanadium {

class OpenGLIndexBuffer : public IndexBuffer {
 private:
  GLuint pointer = 0;
  VNsize size;

 public:
  OpenGLIndexBuffer(const VNuint* indices, VNsize size);
  ~OpenGLIndexBuffer();

  [[nodiscard]] void* getRaw() const noexcept override;
  void bind() const noexcept override;
  void unbind() const noexcept override;
  [[nodiscard]] VNsize getCount() const noexcept override;
  bool operator!() const noexcept override;
};

}  // namespace Vanadium

#endif  // VANADIUM_OPENGLINDEXBUFFER_H
