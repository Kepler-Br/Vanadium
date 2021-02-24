#include "Stopwatch.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultStopwatch.h"
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
    #else
        #error "Not supported platform!"
    #endif
    if (startImmediately)
        stopwatch->start();
    return stopwatch;
}
}