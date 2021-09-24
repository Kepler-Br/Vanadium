#include "SdlWindowFactoryImpl.h"

#include "platform/sdl/SdlWindow.h"

namespace vanadium {

Ref<Window> SdlWindowFactoryImpl::construct(
    const WindowProperties& properties) {
  return MakeRef<SdlWindow>(properties);
}

}  // namespace vanadium
