#include "Window.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultWindow.h"
#elif defined(VANADIUM_PLATFORM_WINDOWS)
    #include "../platform/windows/WindowsWindow.h"
#elif defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/macos/MacOSWindow.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

Window *Window::create(const std::string &title, const glm::ivec2 &geometry)
{
    return Window::create(title, geometry.x, geometry.y);
}

Window *Window::create(const std::string &title, uint32_t width, uint32_t height)
{
    VAN_ENGINE_TRACE("Creating Window.");
    #ifdef VANADIUM_PLATFORM_LINUX
        return new DefaultWindow(title, width, height);
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        return new WindowsWindow(title, width, height);
    #elif defined(VANADIUM_PLATFORM_MACOS)
        return new MacOSWindow(title, width, height);
    #else
        #error "Not supported platform!"
    #endif
}

}