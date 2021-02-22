#include "Timer.h"
#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/linux/LinuxTimer.h"
#endif
#ifdef VANADIUM_PLATFORM_WINDOWS
    #include "../platform/windows/WindowsTimer.h"
#endif
#ifdef VANADIUM_PLATFORM_MACOS
    #include "../platform/macos/MacOSTimer.h"
#endif

namespace Van
{

Timer *Van::Timer::create()
{
    #ifdef VANADIUM_PLATFORM_LINUX
    //        return new LinuxTimer;
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        return new WindowsTimer;
    #elif defined(VANADIUM_PLATFORM_MACOS)
        return new MacOSTimer;
    #endif
    return nullptr;
}
}