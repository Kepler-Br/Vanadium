#include "core/Window.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultWindow.h"
using WindowImpl = vanadium::DefaultWindow;
#endif

namespace vanadium {

Window *Window::create(const WindowProperties &properties) {
  return new WindowImpl(properties);
}

}  // namespace vanadium