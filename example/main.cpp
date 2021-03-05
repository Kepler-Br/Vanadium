#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"

// Todo: Think about adding global/local resource repository.
// Todo: State load resources is not used.
// Todo: add flag to disable file logging and disable logging at all.
// Todo: multithreaded resource loading.
// Todo: check if -DSYSTEM_SDL=1 working.
// Todo: implement FpsCamera.
// Todo: Timer is not using startImmediately.
// Todo: DefaultStopwatch is not implemented.
// Todo: Animation is not implemented.

// Todo: Why does PhysFS says that .zip is NOT_FOUND after mount?
// Todo: Optimize SVG rasterizing.

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

int main(int argc, char** argv)
{
    using namespace Vanadium;



//    std::string source = IO::getInstance()->readAsString("./resources/svgs/OBEYSUDO.svg");
//    Svg::Document *document = Svg::Parser::parse(source);
//    std::cout << "Document resolution: " << document->getDimensions().x << ", " << document->getDimensions().y << std::endl;
//    std::cout << "Document name: " << document->getName() << std::endl;
//    std::cout << "Total layers: " << document->getTotalLayers() << std::endl;
//    std::cout << "Total paths: " << document->getTotalPaths() << std::endl;
//    std::cout << "Total commands: " << document->getTotalCommands() << std::endl;
//    std::vector<VNfloat> rasterized = Svg::Rasterizer::rasterize2D(document, 20);
//    std::cout << "Vertices total: " << rasterized.size() << std::endl;
//    delete document;


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
