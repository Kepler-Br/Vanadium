#include "SdlStopwatchFactoryImpl.h"

#include "vanadium/platform/sdl/SdlStopwatchImpl.h"

namespace vanadium {

Ref<Stopwatch> SdlStopwatchFactoryImpl::construct() {
  return vanadium::Ref<SdlStopwatchImpl>();
}

}  // namespace vanadium
