#include "EventProvider.h"
#include "Window.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/linux/LinuxEventProvider.h"
#endif
#ifdef VANADIUM_PLATFORM_WINDOWS
    #include "../platform/windows/WindowsEventProvider.h"
#endif
#ifdef VANADIUM_PLATFORM_MACOS
    #include "../platform/macos/MacOSEventProvider.h"
#endif

namespace Van
{

EventProvider *EventProvider::create(Window *window)
{
    #ifdef VANADIUM_PLATFORM_LINUX
//        return new LinuxEventProvider(window);
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        return new WindowsEventProvider(window);
    #elif defined(VANADIUM_PLATFORM_MACOS)
        return new MacOSEventProvider(window);
    #else
        #error "Not supported platform!"
    #endif
}

}