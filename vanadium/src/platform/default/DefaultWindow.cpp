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
        const char *message = SDL_GetError();
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 subsystems: {}", message);
        throw InitializationInterrupted(std::string("Cannot initialize SDL2 subsystems: ") + message);
    }
    VAN_ENGINE_INFO("Initializing SDL2 window.");
    this->createWindow();
    this->createContext();
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
        const char *message = SDL_GetError();
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 window: {}", message);
        throw InitializationInterrupted(std::string("Cannot initialize SDL2 window: ") + message);
    }
}

#if !defined(VANADIUM_PLATFORM_MACOS)
// Todo: REMOVE ME.
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
}
#endif

void DefaultWindow::createContext()
{
    int sdlErrorReturn;

#ifdef VANADIUM_RENDERAPI_OPENGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    this->glContext = SDL_GL_CreateContext(this->window);
    if (this->glContext == nullptr)
    {
        const char *message = SDL_GetError();
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 OpenGL context: {}", message);
        throw InitializationInterrupted(std::string("SDL2 OpenGL context initialization error: ") + message);
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
        const GLubyte *message = glewGetErrorString(glewError);
        VAN_ENGINE_CRITICAL("Cannot initialize GLEW: {}", message);
        throw InitializationInterrupted(std::string("Cannot initialize GLEW: ") + (char *)message);
    }

// TODO: REMOVE IT IN OLD OPENGL CORE IMPLEMENTATION.
// During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);
#endif
#else
    #error "Not supported render API."
#endif
}

void DefaultWindow::updateWindowGeometryInformation()
{
    int width, height;

#ifdef VANADIUM_RENDERAPI_OPENGL
    SDL_GL_GetDrawableSize(this->window, &width, &height);
#else
//    SDL_GetWindowSize(this->window, &width, &height);
#error "Not a supported render API."
#endif
    this->specification.width = width;
    this->specification.height = height;
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

std::string DefaultWindow::getTitle() noexcept
{
    return this->specification.title;
}

VNsize DefaultWindow::getWidth() noexcept
{
    this->updateWindowGeometryInformation();
    return this->specification.width;
}

VNsize DefaultWindow::getHeight() noexcept
{
    this->updateWindowGeometryInformation();
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

glm::ivec2 DefaultWindow::getGeometry() noexcept
{
    this->updateWindowGeometryInformation();
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

VNint DefaultWindow::getPositionX() noexcept
{
    SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
    return this->positionX;
}

VNint DefaultWindow::getPositionY() noexcept
{
    SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
    return this->positionY;
}

void DefaultWindow::setPositionX(VNint posX) noexcept
{
    SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
    SDL_SetWindowPosition(this->window, (int)posX, this->positionY);
}

void DefaultWindow::setPositionY(VNint posY) noexcept
{
    SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
    SDL_SetWindowPosition(this->window, this->positionX, (int)posY);
}

glm::ivec2 DefaultWindow::getPosition() noexcept
{
    SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
    return {this->positionX, this->positionY};
}

void DefaultWindow::setPosition(const glm::ivec2 &position)
{
    SDL_SetWindowPosition(this->window, position.x, position.y);
}

void DefaultWindow::grabCursor(bool isCursorGrabbed) noexcept
{
    // Todo: test this.
    SDL_SetWindowGrab(this->window, isCursorGrabbed ? SDL_TRUE : SDL_FALSE);
}

void *DefaultWindow::getRaw() noexcept
{
    return this->window;
}

void DefaultWindow::setVsync(bool isVsync) noexcept
{
    VAN_ENGINE_ERROR("Cannot change vsync within SDL2 implementation.");
}

void DefaultWindow::setDoubleBuffering(bool isDoubleBuffering)
{
    VAN_ENGINE_ERROR("Cannot change double buffering within SDL2 implementation.");
}

bool DefaultWindow::isDoubleBuffering() noexcept
{
    return this->specification.doubleBuffering;
}

void DefaultWindow::setFullScreen(bool isFullScreen)
{
    if (SDL_SetWindowFullscreen(this->window, isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) != 0)
    {
        VAN_ENGINE_ERROR("{}", SDL_GetError());
        return;
    }
    this->specification.fullscreen = isFullScreen;
}

bool DefaultWindow::isFullScreen() noexcept
{
    return this->specification.fullscreen;
}

void DefaultWindow::setResizable(bool isResizable)
{
    SDL_SetWindowResizable(this->window, isResizable ? SDL_TRUE : SDL_FALSE);
    this->specification.resizable = SDL_GetWindowFlags(this->window) & SDL_WINDOW_RESIZABLE;
}

bool DefaultWindow::isResizable() noexcept
{
    return this->specification.resizable;
}

void DefaultWindow::setBorderless(bool isBorderless)
{
    SDL_SetWindowBordered(this->window, isBorderless ? SDL_TRUE : SDL_FALSE);
    this->specification.borderless = SDL_GetWindowFlags(this->window) & SDL_WINDOW_BORDERLESS;
}

bool DefaultWindow::isBorderless() noexcept
{
    return this->specification.borderless;
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
