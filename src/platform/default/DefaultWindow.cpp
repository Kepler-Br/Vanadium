#include "DefaultWindow.h"

#include <SDL2/SDL_image.h>

#include "../../core/Log.h"

namespace Vanadium
{

void DefaultWindow::init()
{
    VAN_ENGINE_INFO("Initializing SDL2 subsystems.");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 subsystems: {}", SDL_GetError());
        throw std::runtime_error("SDL2 initialization error.");
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 image subsystem: {}", IMG_GetError());
        throw std::runtime_error("SDL2 initialization error.");
    }
    this->createWindow();
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


void DefaultWindow::createWindow()
{
#ifdef VANADIUM_RENDERAPI_OPENGL
    this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    this->width, this->height, SDL_WINDOW_OPENGL);
#else
    #error "Not supported render API."
#endif
    if (this->window == nullptr)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 window: {}", SDL_GetError());
        throw std::runtime_error("SDL2 initialization error.");
    }
#ifdef VANADIUM_RENDERAPI_OPENGL
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, SDL_TRUE );
    this->glContext = SDL_GL_CreateContext(window);
    if (this->glContext == nullptr)
    {
        VAN_ENGINE_CRITICAL("Cannot initialize SDL2 OpenGL context: {}", SDL_GetError());
        throw std::runtime_error("SDL2 initialization error.");
    }
#else
    #error "Not supported render API."
#endif
}

DefaultWindow::DefaultWindow(const std::string &title, uint32_t width, uint32_t height)
{
    this->title = title;
    this->width = width;
    this->height = height;
    this->init();
}

DefaultWindow::~DefaultWindow()
{
    VAN_ENGINE_INFO("Destroying SDL2 subsystems.");
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    SDL_Quit();
#ifdef VANADIUM_RENDERAPI_OPENGL
    delete (Sdl2OpenGLNative *)this->native;
#else
    #error "Not supported render API."
#endif
}

void DefaultWindow::setTitle(const std::string &title) noexcept
{
    SDL_SetWindowTitle(this->window, title.c_str());
}

std::string DefaultWindow::getTitle() const noexcept
{
    return this->title;
}

uint32_t DefaultWindow::getWidth() const noexcept
{
    return this->width;
}

uint32_t DefaultWindow::getHeight() const noexcept
{
    return this->height;
}

void DefaultWindow::setWidth(uint32_t width) noexcept
{
    this->width = width;
    SDL_SetWindowSize(this->window, this->width, this->height);
}

void DefaultWindow::setHeight(uint32_t height) noexcept
{
    this->height = height;
    SDL_SetWindowSize(this->window, this->width, this->height);
}

glm::ivec2 DefaultWindow::getGeometry() const noexcept
{
    return {this->width, this->height};
}

void DefaultWindow::setGeometry(const glm::ivec2 &geometry) noexcept
{
    this->width = geometry.x;
    this->height = geometry.y;
    SDL_SetWindowSize(this->window, this->width, this->height);
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