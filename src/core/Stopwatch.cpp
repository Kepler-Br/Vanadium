#include "Stopwatch.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultStopwatch.h"
#elif defined(VANADIUM_PLATFORM_WINDOWS)
    #include "../platform/windows/WindowsTimer.h"
#elif defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/macos/MacOSTimer.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

Stopwatch *Vanadium::Stopwatch::create(bool startImmediately)
{
    Stopwatch *stopwatch;

    VAN_ENGINE_TRACE("Creating Stopwatch.");
    #ifdef VANADIUM_PLATFORM_LINUX
        stopwatch = new DefaultStopwatch;
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        stopwatch = new WindowsStopwatch;
    #elif defined(VANADIUM_PLATFORM_MACOS)
        stopwatch = new MacOSStopwatch;
    #else
        #error "Not supported platform!"
    #endif
    if (startImmediately)
        stopwatch->start();
    return stopwatch;
}
}