#include "Window.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultWindow.h"
#endif
#ifdef VANADIUM_PLATFORM_WINDOWS
    #include "../platform/windows/WindowsWindow.h"
#endif
#ifdef VANADIUM_PLATFORM_MACOS
    #include "../platform/macos/MacOSWindow.h"
#endif

namespace Van
{

Window *Window::create(const std::string &title, const glm::ivec2 &geometry)
{
    return Window::create(title, geometry.x, geometry.y);
}

Window *Window::create(const std::string &title, uint32_t width, uint32_t height)
{
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