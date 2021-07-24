#include "core/EventProvider.h"

#include "core/Log.h"
#include "core/Window.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/sdl/SdlEventProvider.h"
using EventProviderImpl = vanadium::SdlEventProvider;
#endif

namespace vanadium {

Ref<EventProvider> EventProviderFactory::create() {
  VAN_ENGINE_TRACE("Creating EventProvider.");
  return MakeRef<EventProviderImpl>();
}

}  // namespace vanadium
