#include "IO.h"

#include "Log.h"
#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultIO.h"
#elif defined(VANADIUM_PLATFORM_WINDOWS)
    #include "../platform/windows/WindowsTimer.h"
#elif defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/macos/MacOSTimer.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

IO *IO::instance = nullptr;

IO *IO::getInstance()
{
    if (IO::instance == nullptr)
        IO::instance = IO::create();
    return IO::instance;
}

IO *IO::create()
{
    VAN_ENGINE_TRACE("Initializing IO subsystem.");
    #ifdef VANADIUM_PLATFORM_LINUX
        IO::instance = new DefaultIO();
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        #error "Not supported platform."
    #elif defined(VANADIUM_PLATFORM_MACOS)
        #error "Not supported platform."
    #else
        #error "Not supported platform."
    #endif
    return nullptr;
}

}