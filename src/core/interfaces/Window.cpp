#include "Window.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/sdl/SdlWindow.h"
using WindowImpl = vanadium::SdlWindow;
#endif

namespace vanadium {

Ref<Window> Window::create(const WindowProperties &properties) {
  return MakeRef<WindowImpl>(properties);
}

}  // namespace vanadium
