#include "SdlWindowFactoryImpl.h"

#include "platform/sdl/SdlWindowImpl.h"

namespace vanadium {

Ref<Window> SdlWindowFactoryImpl::construct(
    const WindowProperties& properties) {
  return MakeRef<SdlWindowImpl>(properties);
}

}  // namespace vanadium
