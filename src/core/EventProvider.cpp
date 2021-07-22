#include "core/EventProvider.h"

#include "core/Log.h"
#include "core/Window.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultEventProvider.h"
using EventProviderImpl = vanadium::DefaultEventProvider;
#endif

namespace vanadium {

EventProvider *EventProviderFactory::create(Window *window) {
  VAN_ENGINE_TRACE("Creating EventProvider.");
  return new EventProviderImpl(window);
}

}  // namespace Vanadium