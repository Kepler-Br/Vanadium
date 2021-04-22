#include "core/EventProvider.h"

#include "core/Log.h"
#include "core/Window.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
#include "platform/default/DefaultEventProvider.h"
using EventProviderImpl = Vanadium::DefaultEventProvider;
#endif

namespace Vanadium {

EventProvider *EventProviderFactory::create(Window *window) {
  VAN_ENGINE_TRACE("Creating EventProvider.");
  return new EventProviderImpl(window);
}

}  // namespace Vanadium