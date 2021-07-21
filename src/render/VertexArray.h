#ifndef VANADIUM_VERTEXARRAY_H
#define VANADIUM_VERTEXARRAY_H

#include <vector>

#include "../core/Types.h"
#include "VertexBuffer.h"

namespace Vanadium {

class IndexBuffer;

class VertexArray {
 public:
  virtual ~VertexArray() = default;

  virtual void bind() const noexcept = 0;
  virtual void unbind() const noexcept = 0;
  virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
  virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) noexcept = 0;
  [[nodiscard]] virtual const Ref<IndexBuffer> &getIndexBuffer()
      const noexcept = 0;
  [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>> &getVertexBuffers()
      const noexcept = 0;
  [[nodiscard]] virtual void *getRaw() const noexcept = 0;
  virtual bool operator!() const noexcept = 0;
};

class VertexArrayFactory {
 public:
  static Ref<VertexArray> create();
};

}  // namespace Vanadium

#endif  // VANADIUM_VERTEXARRAY_H
