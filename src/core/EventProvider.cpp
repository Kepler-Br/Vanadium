#include "EventProvider.h"
#include "Window.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultEventProvider.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

EventProvider *EventProviderFactory::create(Window *window)
{
    VAN_ENGINE_TRACE("Creating EventProvider.");
    #ifdef VANADIUM_PLATFORM_LINUX
        return new DefaultEventProvider(window);
    #else
        #error "Not supported platform!"
    #endif
}

}