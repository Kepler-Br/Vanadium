#ifndef VANADIUM_OPENGLVERTEXARRAY_H
#define VANADIUM_OPENGLVERTEXARRAY_H

#include <vector>

#include "../../core/Types.h"
#include "../../render/VertexArray.h"

namespace Vanadium {

class OpenGLVertexArray : public VertexArray {
 private:
  std::vector<Ref<VertexBuffer>> vertexBuffers;
  Ref<IndexBuffer> indexBuffer;
  GLuint pointer = 0;
  VNsize vertexBufferIndex = 0;

  static GLenum dataTypeToOpenGLEnum(DataTypes type);

 public:
  OpenGLVertexArray();
  ~OpenGLVertexArray() override;

  void bind() const noexcept override;
  void unbind() const noexcept override;
  void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
  void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) noexcept override;
  [[nodiscard]] const Ref<IndexBuffer> &getIndexBuffer()
      const noexcept override;
  [[nodiscard]] const std::vector<Ref<VertexBuffer>> &getVertexBuffers()
      const noexcept override;
  [[nodiscard]] void *getRaw() const noexcept override;
  bool operator!() const noexcept override;
};

}  // namespace Vanadium

#endif  // VANADIUM_OPENGLVERTEXARRAY_H
