#include "Window.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultWindow.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

Window *WindowFactory::create(const std::string &title, const glm::ivec2 &geometry)
{
    return WindowFactory::create(title, geometry.x, geometry.y);
}

Window *WindowFactory::create(const std::string &title, uint32_t width, uint32_t height)
{
    VAN_ENGINE_TRACE("Creating Window.");
    #ifdef VANADIUM_PLATFORM_LINUX
        return new DefaultWindow(title, width, height);
    #else
        #error "Not supported platform!"
    #endif
}

}