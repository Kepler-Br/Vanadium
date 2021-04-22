#include "core/Stopwatch.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
#include "platform/default/DefaultStopwatch.h"
using StopWatchImpl = Vanadium::DefaultStopwatch;
#else
#error "Not supported platform!"
#endif

namespace Vanadium {

Stopwatch *Vanadium::Stopwatch::create(bool startImmediately) {
  Stopwatch *stopwatch;

  VAN_ENGINE_TRACE("Creating Stopwatch.");
  stopwatch = new StopWatchImpl;
  if (startImmediately) stopwatch->start();
  return stopwatch;
}

}  // namespace Vanadium