#include "Stopwatch.h"
#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/linux/LinuxStopwatch.h"
#endif
#ifdef VANADIUM_PLATFORM_WINDOWS
    #include "../platform/windows/WindowsTimer.h"
#endif
#ifdef VANADIUM_PLATFORM_MACOS
    #include "../platform/macos/MacOSTimer.h"
#endif

namespace Van
{

Stopwatch *Van::Stopwatch::create(bool startImmediately)
{
    Stopwatch *stopwatch;

    #ifdef VANADIUM_PLATFORM_LINUX
        stopwatch = new LinuxStopwatch;
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