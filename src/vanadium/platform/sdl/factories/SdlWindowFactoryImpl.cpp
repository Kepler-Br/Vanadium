#include "SdlWindowFactoryImpl.h"

#include "vanadium/platform/sdl/SdlWindowImpl.h"

namespace vanadium {

SdlWindowFactoryImpl::SdlWindowFactoryImpl(Ref<LoggerFactory> loggerFactory)
    : _loggerFactory(std::move(loggerFactory)) {}

Ref<Window> SdlWindowFactoryImpl::construct(
    const WindowProperties& properties) {
  return MakeRef<SdlWindowImpl>(properties, this->_loggerFactory->construct("Window"));
}

}  // namespace vanadium
