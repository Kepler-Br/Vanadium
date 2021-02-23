#include "EventProvider.h"
#include "Window.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultEventProvider.h"
#elif defined(VANADIUM_PLATFORM_WINDOWS)
    #include "../platform/windows/WindowsEventProvider.h"
#elif defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/macos/MacOSEventProvider.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

EventProvider *EventProvider::create(Window *window)
{
    VAN_ENGINE_TRACE("Creating EventProvider.");
    #ifdef VANADIUM_PLATFORM_LINUX
        return new DefaultEventProvider(window);
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        return new WindowsEventProvider(window);
    #elif defined(VANADIUM_PLATFORM_MACOS)
        return new MacOSEventProvider(window);
    #else
        #error "Not supported platform!"
    #endif
}

}