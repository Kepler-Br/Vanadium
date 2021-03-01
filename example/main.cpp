#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"

// Todo: Think about adding global/local resource repository.
// Todo: State load resources is not used.
// Todo: add flag to disable file logging and disable logging at all.
// Todo: multithreaded resource loading.
// Todo: check if -DSYSTEM_SDL=1 working.
// Todo: check if russian works at application start.
// Todo: implement FpsCamera.

// TODO!!!: VFS CORRUPTS ZIP ARCHIVES!!!
// Todo: Why does PhysFS says that .zip is NOT_FOUND?

class EntryPoint : public Application
{
public:
    // DO NOT THROW HERE!!!
    explicit EntryPoint(const Application::Specification &specs):
        Application(specs)
    {}

    // Application is not initialized here! DO NOT USE ANYTHING FROM APPLICATION(Except program arguments)!!!
    void preInit() override
    {
        if(!Vfs::init(this->programArguments[0]))
            VAN_USER_ERROR("Init: {}", Vfs::getError());
        if(!Vfs::mount("./resources.zip", ""))
        {
            Vfs::ErrorCode error = Vfs::getErrorCode();
            if (error == Vfs::ErrorCode::Unsupported)
            {
                throw InitializationInterrupted(
                        ((std::stringstream()) << "VFS returned \""
                        << Vfs::errorCodeToString(error)
                        << "\". Possible reason is that the archive might be corrupted. "
                        << "Possible by VFS.").str()
                );
            }
            throw InitializationInterrupted(
                    ((std::stringstream())
                    << "VFS mount error. VFS returned \""
                    << Vfs::errorCodeToString(error) << "\"(Code: "
                    << (VNenum)error
                    << ")."
                    ).str());
        }
        else
        {
            Vfs::ErrorCode error = Vfs::getErrorCode();
            // Buggy.
            if (error != Vfs::ErrorCode::OK)

                throw InitializationInterrupted(
                        ((std::stringstream())
                                << "VFS mount error. VFS returned \""
                                << Vfs::errorCodeToString(error) << "\"(Code: "
                                << (VNenum)error
                                << ")."
                        ).str());
        }
        VAN_USER_INFO("Before: {}", Vfs::getError());
        VAN_USER_INFO("Is shader.xml exists: {}", Vfs::exists("resources/shaders/shader.xml"));
//        std::vector<std::string> files = Vfs::listDirectory("resources/shaders");
//        VAN_USER_INFO("After: {}", Vfs::getError());
//        for (const auto &entry : files)
//        {
//            VAN_USER_INFO("File: {}", entry);
//        }
//        if(!PHYSFS_setWriteDir("write"))
//        {
//            PHYSFS_ErrorCode error = PHYSFS_getLastErrorCode();
//            if (error == PHYSFS_ERR_UNSUPPORTED)
//            VAN_USER_INFO("Write dir error: {}", PHYSFS_getErrorByCode(error));
//        }
//        VAN_USER_INFO("Is readonly: {}", Vfs::isReadonly("resources/shaders/shader.xml"));
//        VAN_USER_INFO("Get write dir: {}", PHYSFS_getWriteDir());
//        throw InitializationInterrupted("No", false);
    }

    // Here application is fully initialized.
    void postInit() override
    {
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
    Vfs::deinit();
    return 0;
}
