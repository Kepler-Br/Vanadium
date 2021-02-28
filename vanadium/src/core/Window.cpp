#include "Window.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultWindow.h"
    using WindowImpl = Vanadium::DefaultWindow;
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

Window *Window::create(const Window::Specification &spec)
{
    return new WindowImpl(spec);
}

}