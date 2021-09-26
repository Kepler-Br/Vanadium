#include "DefaultRandomFactoryImpl.h"

#include "vanadium/platform/default/DefaultRandomImpl.h"

namespace vanadium {

Ref<Random> DefaultRandomFactoryImpl::construct() {
  return MakeRef<DefaultRandomImpl>();
}

Ref<Random> DefaultRandomFactoryImpl::construct(uint64_t seed) {
  return MakeRef<DefaultRandomImpl>(seed);
}

}  // namespace vanadium
