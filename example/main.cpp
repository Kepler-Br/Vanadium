#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"

#warning "Think about adding global resource repository."
#warning "State load resources is not used."
// Todo: add flag to disable file logging and disable logging at all.
// Todo: multithreaded resource loading.
// Todo: add option to use system's SDL2.

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

#include "../vanadium/src/vfs/Vfs.h"

int main(int argc, char** argv)
{
    using namespace Vanadium;

    // No tag-based init for structures in C++ :'(.
    // Todo: refactor me.
    Window::Specification winSpecs(800, 600);
    winSpecs.title = "Oh, my~";
    winSpecs.resizable = true;
    Application::Specification appSpecs;
    appSpecs.winSpecs = winSpecs;
    appSpecs.argc = argc;
    appSpecs.argv = argv;
//    Log::init();
//    if(!Vfs::init(argv[0]))
//        VAN_USER_ERROR(Vfs::getError());
//    Vfs::mount("gamedata.zip", "");
//    std::vector<std::string> files = Vfs::listDirectory("example");
//    for (const auto &entry : files)
//    {
//        VAN_USER_INFO(entry);
//    }
//    Vfs::deinit();
    PHYSFS_init(argv[0]);
    PHYSFS_deinit();
    auto *app = new EntryPoint(appSpecs);
    app->init();
    app->pushState<CustomState>("Custom state");
    app->run();
    delete app;
    return 0;
}
