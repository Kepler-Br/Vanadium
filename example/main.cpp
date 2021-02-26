#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"
#include <iostream>

#warning "Implement state commands."
#warning "Add OnWindowStopResizingEvent."
#warning "Add vendor information on start."
#warning "Deal with GLEW compilation."
#warning "Add VFS."

class EntryPoint : public Application
{
public:
    explicit EntryPoint(const Application::Specification &specs):
        Application(specs)
    {
        for (const auto &arg : this->programArguments)
        {
            std::cout << arg << std::endl;
        }
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
    Application::Specification appSpecs;
    appSpecs.winSpecs = winSpecs;
    appSpecs.argc = argc;
    appSpecs.argv = argv;
    auto *app = new EntryPoint(appSpecs);
    app->init();
    app->forcePushState<CustomState>("Custom state");
//    app->run();
    delete app;
    return 0;
}
