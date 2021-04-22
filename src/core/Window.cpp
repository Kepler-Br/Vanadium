#include "core/Window.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
#include "platform/default/DefaultWindow.h"
using WindowImpl = Vanadium::DefaultWindow;
#endif

namespace Vanadium {

Window *Window::create(const Window::Specification &spec) {
  return new WindowImpl(spec);
}

}  // namespace Vanadium