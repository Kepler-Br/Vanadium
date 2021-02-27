#include "DefaultWindow.h"

#include <utility>

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../opengl/OpenGLIncludes.h"
#endif

#include "../../core/Log.h"
#include "../../core/Exceptions.h"

namespace Vanadium
{

void DefaultWindow::init()
{
    VAN_ENGINE_INFO("Initializing SDL2 subsystems.");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 subsystems: {}", SDL_GetError());
        throw InitializationInterrupted("SDL2 initialization error. See logs.");
    }
    VAN_ENGINE_INFO("Initializing SDL2 window.");
    this->createWindow();
    this->createContext();
    this->updateNativeStruct();
}

void DefaultWindow::updateNativeStruct()
{
#ifdef VANADIUM_RENDERAPI_OPENGL
    Sdl2OpenGLNative *nativeStruct;
    if (this->native == nullptr)
        this->native = new Sdl2OpenGLNative;
    nativeStruct = (Sdl2OpenGLNative *)this->native;
    nativeStruct->window = this->window;
    nativeStruct->glContext = this->glContext;
#else
    #error "Not supported render API."
#endif
}

// Todo: split this into smaller functions.
void DefaultWindow::createWindow()
{
    VNenum isResizable = this->specification.resizable ? SDL_WINDOW_RESIZABLE : 0;
    VNenum isBorderless = this->specification.borderless ? SDL_WINDOW_BORDERLESS : 0;
    VNenum isInvisible = this->specification.invisible ? SDL_WINDOW_HIDDEN : 0;
    VNenum isFullscreen = this->specification.fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    int sdlErrorReturn;
#ifdef VANADIUM_RENDERAPI_OPENGL
    sdlErrorReturn = SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,
                                          this->specification.doubleBuffering ? SDL_TRUE : SDL_FALSE);
    if (sdlErrorReturn != 0)
    {
        VAN_ENGINE_ERROR("Cannot set SDL double buffering to {}. Error: {}",
                         this->specification.doubleBuffering, SDL_GetError());
    }
    this->window = SDL_CreateWindow(this->specification.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    this->specification.width, this->specification.height,
                                    SDL_WINDOW_OPENGL | isResizable | isBorderless | isInvisible | isFullscreen);
#else
    #error "Not supported render API."
#endif
    if (this->window == nullptr)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 window: {}", SDL_GetError());
        throw InitializationInterrupted("SDL2 initialization error. See logs.");
    }
}

void DefaultWindow::createContext()
{
    int sdlErrorReturn;

#ifdef VANADIUM_RENDERAPI_OPENGL
    this->glContext = SDL_GL_CreateContext(this->window);
    if (this->glContext == nullptr)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 OpenGL context: {}", SDL_GetError());
        throw InitializationInterrupted("SDL2 OpenGL context initialization error. See logs.");
    }
    sdlErrorReturn = SDL_GL_SetSwapInterval(this->specification.vSync ? 1 : 0);
    if (sdlErrorReturn != 0)
    {
        VAN_ENGINE_ERROR("Cannot set SDL vsync to {}. Error: {}",
                         this->specification.vSync, SDL_GetError());
    }
    VAN_ENGINE_INFO("OpenGL Info:");
    VAN_ENGINE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    VAN_ENGINE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    VAN_ENGINE_INFO("  Version: {0}", glGetString(GL_VERSION));
#ifndef __APPLE__
    GLenum glewError = glewInit();
    if (GLEW_OK != glewError)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize GLEW: {}", glewGetErrorString(glewError));
        throw InitializationInterrupted("GLEW initialization error. See logs.");
    }
#endif
#else
    #error "Not supported render API."
#endif
}

DefaultWindow::DefaultWindow(Window::Specification spec):
    specification(std::move(spec))
{
    this->init();
}

DefaultWindow::~DefaultWindow()
{
    VAN_ENGINE_INFO("Destroying window.");

#ifdef VANADIUM_RENDERAPI_OPENGL
    SDL_GL_DeleteContext(this->glContext);
    delete (Sdl2OpenGLNative *)this->native;
#else
    #error "Not a supported render API."
#endif
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void DefaultWindow::setTitle(const std::string &title) noexcept
{
    SDL_SetWindowTitle(this->window, title.c_str());
    this->specification.title = title;
}

std::string DefaultWindow::getTitle() const noexcept
{
    return this->specification.title;
}

VNsize DefaultWindow::getWidth() const noexcept
{
    return this->specification.width;
}

VNsize DefaultWindow::getHeight() const noexcept
{
    return this->specification.height;
}

void DefaultWindow::setWidth(VNsize width) noexcept
{
    this->specification.width = width;
    SDL_SetWindowSize(this->window,
                      this->specification.width,
                      this->specification.height);
}

void DefaultWindow::setHeight(VNsize height) noexcept
{
    this->specification.height = height;
    SDL_SetWindowSize(this->window,
                      this->specification.width,
                      this->specification.height);
}

glm::ivec2 DefaultWindow::getGeometry() const noexcept
{
    return {this->specification.width,
            this->specification.height};
}

void DefaultWindow::setGeometry(const glm::ivec2 &geometry) noexcept
{
    this->specification.width = geometry.x;
    this->specification.height = geometry.y;
    SDL_SetWindowSize(this->window,
                      this->specification.width,
                      this->specification.height);
}

void *DefaultWindow::getNative() const noexcept
{
    return this->native;
}

void DefaultWindow::setVsync(bool isVsync) noexcept
{
    VAN_ENGINE_ERROR("Cannot change vsync within SDL2 implementation.");
}

void DefaultWindow::setDoubleBuffering(bool isDoubleBuffering)
{
    VAN_ENGINE_ERROR("Cannot change double buffering within SDL2 implementation.");
}

void DefaultWindow::swapBuffer()
{
#ifdef VANADIUM_RENDERAPI_OPENGL
    SDL_GL_SwapWindow(this->window);
#else
    #error "Not supported render API."
#endif
}

}
