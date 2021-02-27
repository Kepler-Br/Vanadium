#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"
#include <iostream>

#warning "Add VFS."
#warning "Think about going from GLEW to GLAD."
#warning "Think about adding global resource repository."
#warning "Fix event callback loss on state push."

class EntryPoint : public Application
{
public:
    explicit EntryPoint(const Application::Specification &specs):
        Application(specs)
    {
        VAN_USER_INFO("Executing constructor.");
    }

    void preInit() override
    {
        VAN_USER_INFO("Executing preInit.");
    }

    void postInit() override
    {
        VAN_USER_INFO("Executing postInit.");
    }
};


int main(int argc, char** argv)
{
    using namespace Vanadium;

    // No tag-based init for structures in C++ :'(.
    // Todo: refactor me.
    Window::Specification winSpecs;
    winSpecs.width = 800;
    winSpecs.height = 600;
    winSpecs.title = "Oh, my~";
    winSpecs.resizable = true;
    Application::Specification appSpecs;
    appSpecs.winSpecs = winSpecs;
    appSpecs.argc = argc;
    appSpecs.argv = argv;

    auto *app = new EntryPoint(appSpecs);
    app->init();
    app->pushState<CustomState>("Custom state");
    app->run();
    delete app;
    return 0;
}
