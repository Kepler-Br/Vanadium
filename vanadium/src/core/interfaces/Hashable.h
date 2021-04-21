#ifndef VANADIUM_HASHABLE_H
#define VANADIUM_HASHABLE_H

#include "../Types.h"

namespace Vanadium {

class Hashable {
 public:
  [[nodiscard]] virtual VNsize hashCode() const noexcept = 0;
};

}  // namespace Vanadium

#endif  // VANADIUM_HASHABLE_H
