#ifndef VANADIUM_INDEXBUFFER_H
#define VANADIUM_INDEXBUFFER_H

#include <vector>

#include "../core/Types.h"

namespace Vanadium {

class IndexBuffer {
 public:
  [[nodiscard]] virtual void *getRaw() const noexcept = 0;
  virtual void bind() const noexcept = 0;
  virtual void unbind() const noexcept = 0;
  [[nodiscard]] virtual VNsize getCount() const noexcept = 0;
  virtual bool operator!() const noexcept = 0;
};

class IndexBufferFactory {
 public:
  static Ref<IndexBuffer> create(const std::vector<VNuint> &data);
  static Ref<IndexBuffer> create(const VNuint *data, VNsize count);
};

}  // namespace Vanadium

#endif  // VANADIUM_INDEXBUFFER_H
