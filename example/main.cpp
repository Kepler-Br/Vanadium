#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"

// Todo: Think about adding global/local resource repository.
// Todo: State load resources is not used.
// Todo: add flag to disable file logging and disable logging at all.
// Todo: multithreaded resource loading.
// Todo: check if -DSYSTEM_SDL=1 working.
// Todo: Timer is not using startImmediately.
// Todo: Animation is not implemented.

// Todo: Why does PhysFS says that .zip is NOT_FOUND after mount?
// Todo: Optimize SVG rasterizing.
// Todo: Remove render window borders.
// Todo: Add patch aura affect.
// Todo: fix random string randomness.
// Todo: fix coordinate bug.

#include "stb_image.h"

class EntryPoint : public Application
{
public:
    // DO NOT THROW HERE!!!
    explicit EntryPoint(const Application::Specification &specs):
        Application(specs)
    {
        // Todo: Move this to another place.
        stbi_set_flip_vertically_on_load(true);
    }

    // Application is not initialized here! DO NOT USE ANYTHING FROM APPLICATION(Except program arguments)!!!
    void preInit() override
    {
        if(!Vfs::init(this->programArguments[0]))
            VAN_USER_ERROR("Init: {}", Vfs::getError());
        if(!Vfs::mount("resources", ""))
        {
            std::stringstream msg;
            Vfs::ErrorCode error = Vfs::getErrorCode();
            if (error == Vfs::ErrorCode::Unsupported)
            {
                throw InitializationInterrupted(
                        dynamic_cast<std::stringstream&>
                        (msg << "VFS returned \""
                        << Vfs::errorCodeToString(error)
                        << "\". Possible reason is that the archive might be corrupted. "
                        << "Possible by VFS.").str(), false
                );
            }
            throw InitializationInterrupted(
                    dynamic_cast<std::stringstream&>
                    (msg
                    << "VFS mount error. VFS returned \""
                    << Vfs::errorCodeToString(error) << "\"(Code: "
                    << (VNenum)error
                    << ")."
                    ).str(), false);
        }
        else
        {
            // Bug in PhysFS. PhysFS throws NOT_FOUND on archive mount.
            Vfs::discardErrors();
        }
    }

    // Here application is fully initialized. You may load OpenGL resources.
    void postInit() override
    {
    }
};


#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>



int main(int argc, char** argv)
{
    using namespace Vanadium;

    // No tag-based init for structures in C++ :'(.
    // Todo: refactor me.
    Window::Specification winSpecs(900, 800);
    winSpecs.title = "Shapeshifter";
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
    Vfs::deinit();
    return 0;
}
