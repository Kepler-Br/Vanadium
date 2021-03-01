#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"

// Todo: Think about adding global/local resource repository.
// Todo: State load resources is not used.
// Todo: add flag to disable file logging and disable logging at all.
// Todo: multithreaded resource loading.
// Todo: check if -DSYSTEM_SDL=1 working.
// Todo: check if russian works at application start.
// Todo: implement FpsCamera.

// TODO!!!: VFS IS NOT WORKING!!!

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
        if(!Vfs::init(this->programArguments[0]))
            VAN_USER_ERROR(Vfs::getError());
        if(!Vfs::mount("resources.zip", ""))
            VAN_USER_ERROR(Vfs::getError());
        std::vector<std::string> files = Vfs::listDirectory("resources/shaders");
        for (const auto &entry : files)
        {
            VAN_USER_INFO("File: {}", entry);
        }
        VAN_USER_INFO("Filesize: {}", Vfs::isReadonly("resources/shaders/shader.xml"));
//        Vfs::FileStream file;
//        file.open("resources/shaders/shader.xml", Vfs::OpenMode::Input);
//        if(!file)
//        {
//            VAN_USER_INFO("Error openning file \"{}\"", Vfs::getError());
//        }
        Vfs::deinit();
        throw InitializationInterrupted("No", false);
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
    Window::Specification winSpecs(800, 600);
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
