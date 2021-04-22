#ifndef VANADIUM_OPENGLVERTEXBUFFER_H
#define VANADIUM_OPENGLVERTEXBUFFER_H

#include "../../core/Types.h"
#include "../../render/VertexBuffer.h"
#include "OpenGLIncludes.h"

namespace Vanadium {

// Stolen from The Cherno. Check out his youtube channel:
// https://www.youtube.com/user/TheChernoProject
class OpenGLVertexBuffer : public VertexBuffer {
 private:
  GLuint pointer = 0;
  VNsize sizeInBytes;
  VertexBuffer::Layout layout;

 public:
  OpenGLVertexBuffer(const void *data, VNsize size, VertexBuffer::Usage usage);
  ~OpenGLVertexBuffer();

  [[nodiscard]] void *getRaw() const noexcept override;
  void bind() const noexcept override;
  void unbind() const noexcept override;
  void setData(const void *data, VNsize sizeInBytes) override;
  [[nodiscard]] const VertexBuffer::Layout &getLayout() const override;
  void setLayout(const VertexBuffer::Layout &layout) override;
  bool operator!() const noexcept override;

  static GLenum usageToOpenGLUsage(Usage usage);
};

}  // namespace Vanadium

#endif  // VANADIUM_OPENGLVERTEXBUFFER_H
