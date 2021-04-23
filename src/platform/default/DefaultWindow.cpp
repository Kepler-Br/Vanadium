#include "platform/default/DefaultWindow.h"

#include <utility>

#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "platform/opengl/OpenGLIncludes.h"
#endif

#include "core/Exceptions.h"
#include "core/Log.h"

namespace Vanadium {

void DefaultWindow::init() {
  VAN_ENGINE_INFO("Initializing SDL2 subsystems.");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    const char *message = SDL_GetError();
    VAN_ENGINE_CRITICAL("Cannot initialize SDL2 subsystems: {}", message);
    throw InitializationInterrupted(
        std::string("Cannot initialize SDL2 subsystems: ") + message);
  }
  VAN_ENGINE_INFO("Initializing SDL2 window.");
  this->createWindow();
  this->createContext();
}

void DefaultWindow::createWindow() {
  VNenum isResizable = this->properties.resizable ? SDL_WINDOW_RESIZABLE : 0;
  VNenum isBorderless =
      this->properties.borderless ? SDL_WINDOW_BORDERLESS : 0;
  VNenum isInvisible = this->properties.invisible ? SDL_WINDOW_HIDDEN : 0;
  VNenum isFullscreen =
      this->properties.fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
  int sdlErrorReturn;
#ifdef VANADIUM_RENDERAPI_OPENGL
  sdlErrorReturn = SDL_GL_SetAttribute(
      SDL_GL_DOUBLEBUFFER,
      this->properties.doubleBuffering ? SDL_TRUE : SDL_FALSE);
  if (sdlErrorReturn != 0) {
    VAN_ENGINE_ERROR("Cannot set SDL double buffering to {}. Error: {}",
                     this->properties.doubleBuffering, SDL_GetError());
  }
  this->window = SDL_CreateWindow(
      this->properties.title.c_str(), SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, (int)this->properties.width,
      (int)this->properties.height,
      SDL_WINDOW_OPENGL | isResizable | isBorderless | isInvisible |
          isFullscreen);
#endif
  if (this->window == nullptr) {
    const char *message = SDL_GetError();
    VAN_ENGINE_CRITICAL("Cannot initialize SDL2 window: {}", message);
    throw InitializationInterrupted(
        std::string("Cannot initialize SDL2 window: ") + message);
  }
}

void DefaultWindow::createContext() {
  int sdlErrorReturn;

#ifdef VANADIUM_RENDERAPI_OPENGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  this->glContext = SDL_GL_CreateContext(this->window);
  if (this->glContext == nullptr) {
    const char *message = SDL_GetError();
    VAN_ENGINE_CRITICAL("Cannot initialize SDL2 OpenGL context: {}", message);
    throw InitializationInterrupted(
        std::string("SDL2 OpenGL context initialization error: ") + message);
  }
  sdlErrorReturn = SDL_GL_SetSwapInterval(this->properties.vSync ? 1 : 0);
  if (sdlErrorReturn != 0) {
    VAN_ENGINE_ERROR("Cannot set SDL vsync to {}. Error: {}",
                     this->properties.vSync, SDL_GetError());
  }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  VAN_ENGINE_INFO("OpenGL Info:");
  VAN_ENGINE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
  VAN_ENGINE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  VAN_ENGINE_INFO("  Version: {0}", glGetString(GL_VERSION));
#ifndef VANADIUM_PLATFORM_MACOS
  glewExperimental = true;
  GLenum glewError = glewInit();
  if (GLEW_OK != glewError) {
    const GLubyte *message = glewGetErrorString(glewError);
    VAN_ENGINE_CRITICAL("Cannot initialize GLEW: {}", message);
    throw InitializationInterrupted(std::string("Cannot initialize GLEW: ") +
                                    (char *)message);
  }

  // TODO: REMOVE IT IN OLD OPENGL CORE IMPLEMENTATION.
  // During init, enable debug output
  glEnable(GL_DEBUG_OUTPUT);
//    glDebugMessageCallback(MessageCallback, nullptr);
#endif
#endif
}

void DefaultWindow::updateWindowGeometryInformation() {
  int width, height;

#ifdef VANADIUM_RENDERAPI_OPENGL
  SDL_GL_GetDrawableSize(this->window, &width, &height);
#endif
  this->properties.width = (VNsize)width;
  this->properties.height = (VNsize)height;
}

DefaultWindow::DefaultWindow(Window::Properties spec)
    : properties(std::move(spec)) {
  this->init();
}

DefaultWindow::~DefaultWindow() {
  VAN_ENGINE_INFO("Destroying window.");

#ifdef VANADIUM_RENDERAPI_OPENGL
  SDL_GL_DeleteContext(this->glContext);
#endif
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void DefaultWindow::setTitle(const std::string &title) noexcept {
  SDL_SetWindowTitle(this->window, title.c_str());
  this->properties.title = title;
}

std::string DefaultWindow::getTitle() noexcept {
  return this->properties.title;
}

VNsize DefaultWindow::getWidth() noexcept {
  this->updateWindowGeometryInformation();
  return this->properties.width;
}

VNsize DefaultWindow::getHeight() noexcept {
  this->updateWindowGeometryInformation();
  return this->properties.height;
}

void DefaultWindow::setWidth(VNsize width) noexcept {
  this->properties.width = width;
  SDL_SetWindowSize(this->window, (int)this->properties.width,
                    (int)this->properties.height);
}

void DefaultWindow::setHeight(VNsize height) noexcept {
  this->properties.height = height;
  SDL_SetWindowSize(this->window, (int)this->properties.width,
                    (int)this->properties.height);
}

glm::ivec2 DefaultWindow::getGeometry() noexcept {
  this->updateWindowGeometryInformation();
  return {(int)this->properties.width, (int)this->properties.height};
}

void DefaultWindow::setGeometry(const glm::ivec2 &geometry) noexcept {
  this->properties.width = (VNsize)geometry.x;
  this->properties.height = (VNsize)geometry.y;
  SDL_SetWindowSize(this->window, (int)this->properties.width,
                    (int)this->properties.height);
}

VNfloat DefaultWindow::getAspect() noexcept {
  return (VNfloat)this->properties.width /
         (VNfloat)this->properties.height;
}

VNint DefaultWindow::getPositionX() noexcept {
  SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
  return this->positionX;
}

VNint DefaultWindow::getPositionY() noexcept {
  SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
  return this->positionY;
}

void DefaultWindow::setPositionX(VNint posX) noexcept {
  SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
  SDL_SetWindowPosition(this->window, (int)posX, this->positionY);
}

void DefaultWindow::setPositionY(VNint posY) noexcept {
  SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
  SDL_SetWindowPosition(this->window, this->positionX, (int)posY);
}

glm::ivec2 DefaultWindow::getPosition() noexcept {
  SDL_GetWindowPosition(this->window, &this->positionX, &this->positionY);
  return {this->positionX, this->positionY};
}

void DefaultWindow::setPosition(const glm::ivec2 &position) {
  SDL_SetWindowPosition(this->window, position.x, position.y);
}

void DefaultWindow::grabCursor(bool isCursorGrabbed) noexcept {
  SDL_SetRelativeMouseMode(isCursorGrabbed ? SDL_TRUE : SDL_FALSE);
}

bool DefaultWindow::isCursorGrabbed() noexcept {
  return SDL_GetRelativeMouseMode();
}

void *DefaultWindow::getRaw() noexcept { return this->window; }

void *DefaultWindow::getContext() noexcept { return this->glContext; }

void DefaultWindow::setVsync(bool isVsync) noexcept {
  VAN_ENGINE_ERROR("Cannot change vsync within SDL2 implementation.");
}

void DefaultWindow::setDoubleBuffering(bool isDoubleBuffering) {
  VAN_ENGINE_ERROR(
      "Cannot change double buffering within SDL2 implementation.");
}

bool DefaultWindow::isDoubleBuffering() noexcept {
  return this->properties.doubleBuffering;
}

void DefaultWindow::setFullScreen(bool isFullScreen) {
  if (SDL_SetWindowFullscreen(
          this->window, isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) !=
      0) {
    VAN_ENGINE_ERROR("{}", SDL_GetError());
    return;
  }
  this->properties.fullscreen = isFullScreen;
}

bool DefaultWindow::isFullScreen() noexcept {
  return this->properties.fullscreen;
}

void DefaultWindow::setResizable(bool isResizable) {
  SDL_SetWindowResizable(this->window, isResizable ? SDL_TRUE : SDL_FALSE);
  this->properties.resizable =
      (bool)SDL_GetWindowFlags(this->window) & SDL_WINDOW_RESIZABLE;
}

bool DefaultWindow::isResizable() noexcept {
  return this->properties.resizable;
}

void DefaultWindow::setBorderless(bool isBorderless) {
  SDL_SetWindowBordered(this->window, isBorderless ? SDL_TRUE : SDL_FALSE);
  this->properties.borderless =
      (bool)SDL_GetWindowFlags(this->window) & SDL_WINDOW_BORDERLESS;
}

bool DefaultWindow::isBorderless() noexcept {
  return this->properties.borderless;
}

void DefaultWindow::swapBuffer() {
#ifdef VANADIUM_RENDERAPI_OPENGL
  SDL_GL_SwapWindow(this->window);
#endif
}

}  // namespace Vanadium
