#include "core/Stopwatch.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultStopwatch.h"
using StopWatchImpl = vanadium::DefaultStopwatch;
#endif

namespace vanadium {

Ref<Stopwatch> Stopwatch::create(bool startImmediately) {
  Ref<Stopwatch> stopwatch = MakeRef<StopWatchImpl>();
  if (startImmediately) {
    stopwatch->start();
  }
  return stopwatch;
}

}  // namespace vanadium
