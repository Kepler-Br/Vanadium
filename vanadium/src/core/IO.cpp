#include "IO.h"

#include "Log.h"
#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/default/DefaultIO.h"
    using IOImpl = Vanadium::DefaultIO;
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
    IO::instance = new IOImpl();
    return IO::instance;
}

}