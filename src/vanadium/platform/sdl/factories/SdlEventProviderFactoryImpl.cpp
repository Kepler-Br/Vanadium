#include "SdlEventProviderFactoryImpl.h"

#include "vanadium/platform/sdl/SdlEventProviderImpl.h"

namespace vanadium {

SdlEventProviderFactoryImpl::SdlEventProviderFactoryImpl(
    Ref<LoggerFactory> loggerFactory) {
  this->_loggerFactory = std::move(loggerFactory);
}

Ref<EventProvider> SdlEventProviderFactoryImpl::construct() {
  return MakeRef<SdlEventProviderImpl>(this->_loggerFactory);
}

const std::string& SdlEventProviderFactoryImpl::getImplName() const noexcept {
  return this->_implName;
}

}  // namespace vanadium
