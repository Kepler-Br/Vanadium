#include "DefaultEventDispatcherFactoryImpl.h"

#include "vanadium/platform/default/DefaultEventDispatcherImpl.h"

namespace vanadium {

Ref<EventDispatcher> DefaultEventDispatcherFactoryImpl::construct() {
  return MakeRef<DefaultEventDispatcherImpl>();
}

const std::string& DefaultEventDispatcherFactoryImpl::getImplName()
    const noexcept {
  return this->_implName;
}

}  // namespace vanadium
