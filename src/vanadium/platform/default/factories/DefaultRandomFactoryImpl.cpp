#include "DefaultRandomFactoryImpl.h"

#include "vanadium/platform/default/DefaultRandomImpl.h"

namespace vanadium {

const std::string DefaultRandomFactoryImpl::_implName =
    "DefaultRandomFactoryImpl";

Ref<Random> DefaultRandomFactoryImpl::construct() {
  return MakeRef<DefaultRandomImpl>();
}

Ref<Random> DefaultRandomFactoryImpl::construct(uint64_t seed) {
  return MakeRef<DefaultRandomImpl>(seed);
}

const std::string &DefaultRandomFactoryImpl::getImplName() const noexcept {
  return DefaultRandomFactoryImpl::_implName;
}

}  // namespace vanadium
