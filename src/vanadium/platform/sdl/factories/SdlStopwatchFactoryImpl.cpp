#include "SdlStopwatchFactoryImpl.h"

#include "vanadium/platform/sdl/SdlStopwatchImpl.h"

namespace vanadium {

const std::string SdlStopwatchFactoryImpl::_implName =
    "SdlStopwatchFactoryImpl";

Ref<Stopwatch> SdlStopwatchFactoryImpl::construct() {
  return MakeRef<SdlStopwatchImpl>();
}

const std::string &SdlStopwatchFactoryImpl::getImplName() const noexcept {
  return SdlStopwatchFactoryImpl::_implName;
}

}  // namespace vanadium
