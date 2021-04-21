#include "Window.h"

#include "Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
#include "../platform/default/DefaultWindow.h"
using WindowImpl = Vanadium::DefaultWindow;
#else
#error "Not supported platform!"
#endif

namespace Vanadium {

Window *Window::create(const Window::Specification &spec) {
  return new WindowImpl(spec);
}

}  // namespace Vanadium