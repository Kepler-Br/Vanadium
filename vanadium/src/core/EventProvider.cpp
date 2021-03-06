#include "EventProvider.h"
#include "Window.h"
#include "Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/default/DefaultEventProvider.h"
    using EventProviderImpl = Vanadium::DefaultEventProvider;
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

EventProvider *EventProviderFactory::create(Window *window)
{
    VAN_ENGINE_TRACE("Creating EventProvider.");
    return new EventProviderImpl(window);
}

}