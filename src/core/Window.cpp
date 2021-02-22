#include "Window.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/linux/LinuxWindow.h"
#endif
#ifdef VANADIUM_PLATFORM_WINDOWS
    #include "../platform/windows/WindowsWindow.h"
#endif
#ifdef VANADIUM_PLATFORM_OSX
    #include "../platform/osx/OSXWindow.h"
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
        return LinuxWindow(title, width, height);
    #endif
    #ifdef VANADIUM_PLATFORM_WINDOWS
        return WindowsWindow(title, width, height);
    #endif
    #ifdef VANADIUM_PLATFORM_OSX
        return OSXWindow(title, width, height);
    #endif
    return nullptr;
}

}