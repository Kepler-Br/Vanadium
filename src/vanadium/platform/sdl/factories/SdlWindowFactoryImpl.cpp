#include "SdlWindowFactoryImpl.h"

#include "vanadium/platform/sdl/SdlWindowImpl.h"

namespace vanadium {

const std::string SdlWindowFactoryImpl::_implName = "SdlWindowFactoryImpl";

SdlWindowFactoryImpl::SdlWindowFactoryImpl(Ref<LoggerFactory> loggerFactory)
    : _loggerFactory(std::move(loggerFactory)) {}

Ref<Window> SdlWindowFactoryImpl::construct(
    const WindowProperties& properties) {
  return MakeRef<SdlWindowImpl>(properties,
                                this->_loggerFactory->construct("Window"));
}

const std::string& SdlWindowFactoryImpl::getImplName() const noexcept {
  return SdlWindowFactoryImpl::_implName;
}

}  // namespace vanadium
