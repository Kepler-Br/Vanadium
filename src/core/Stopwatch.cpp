#include "core/Stopwatch.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultStopwatch.h"
using StopWatchImpl = vanadium::DefaultStopwatch;
#endif

namespace vanadium {

Stopwatch *vanadium::Stopwatch::create(bool startImmediately) {
  Stopwatch *stopwatch;

  VAN_ENGINE_TRACE("Creating Stopwatch.");
  stopwatch = new StopWatchImpl;
  if (startImmediately) stopwatch->start();
  return stopwatch;
}

}  // namespace Vanadium