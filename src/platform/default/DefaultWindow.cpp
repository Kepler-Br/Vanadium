#include "platform/default/DefaultWindow.h"

#include <SDL_syswm.h>
#include <bgfx/bgfx.h>

#include "core/Exceptions.h"
#include "core/Log.h"

namespace vanadium {

void DefaultWindow::init(const WindowProperties &properties) {
  VAN_ENGINE_TRACE("Initializing SDL2 subsystems.");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    const char *message = SDL_GetError();
    const std::string errorMessage =
        fmt::format("Cannot initialize SDL2 subsystems: {}", message);
    VAN_ENGINE_CRITICAL(errorMessage);
    throw InitializationInterrupted(errorMessage);
  }
  VAN_ENGINE_TRACE("Initializing SDL2 window.");
  this->createWindow(properties);
  this->createContext(properties);
}

void DefaultWindow::createWindow(const WindowProperties &properties) {
  int sdlErrorReturn;
  Uint32 windowFlags = 0;

  if (properties.getGeometry().x <= 0 || properties.getGeometry().y <= 0) {
    throw InitializationInterrupted("Window geometry is invalid!");
  }
  if (properties.getType() == WindowType::Borderless) {
    windowFlags |= SDL_WINDOW_BORDERLESS;
  } else if (this->windowType == WindowType::Fullscreen) {
    windowFlags |= SDL_WINDOW_FULLSCREEN;
  } else if (this->windowType == WindowType::Resizable) {
    windowFlags |= SDL_WINDOW_RESIZABLE;
  }
  std::optional<glm::ivec2> position = properties.getPosition();
  glm::ivec2 geometry = properties.getGeometry();

  this->window = SDL_CreateWindow(
      this->title.c_str(),
      position.has_value() ? position->x : SDL_WINDOWPOS_CENTERED,
      position.has_value() ? position->y : SDL_WINDOWPOS_CENTERED, geometry.x,
      geometry.y, windowFlags);
  if (this->window == nullptr) {
    const std::string message =
        fmt::format("Cannot initialize SDL2 window: {}", SDL_GetError());
    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }
}

void DefaultWindow::createContext(const WindowProperties &properties) {
  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  if (!SDL_GetWindowWMInfo(this->window, &wmi)) {
    const std::string message = "Cannot get SDL2 window info.";
    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }
  bgfx::Init init;

#if VANADIUM_PLATFORM_LINUX
  init.platformData.ndt = wmi.info.x11.display;
  init.platformData.nwh = (void *)wmi.info.x11.window;
#elif VANADIUM_PLATFORM_MACOS
  init.platformData.ndt = nullptr;
  init.platformData.nwh = wmi.info.cocoa.window;
#elif VANADIUM_PLATFORM_WINDOWS
  init.platformData.ndt = nullptr;
  init.platformData.nwh = wmi.info.win.window;
#endif
  init.resolution.width = properties.getGeometry().x;
  init.resolution.height = properties.getGeometry().y;
  init.resolution.reset =
      properties.getVSync() ? BGFX_RESET_VSYNC : BGFX_RESET_NONE;
  init.callback = &this->bgfxCallback;
  if (!bgfx::init(init)) {
    const std::string message = "Error initializing bgfx.";
    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }

  const bgfx::ViewId kClearView = 0;
  bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
  bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
}

DefaultWindow::DefaultWindow(const WindowProperties &properties)
    : title(properties.getTitle()), windowType(properties.getType()) {
  this->init(properties);
}

DefaultWindow::~DefaultWindow() {
  VAN_ENGINE_TRACE("Destroying window.");

  bgfx::shutdown();
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void DefaultWindow::setTitle(const std::string &newTitle) noexcept {
  SDL_SetWindowTitle(this->window, title.c_str());
  this->title = newTitle;
}

std::string DefaultWindow::getTitle() noexcept { return this->title; }

void DefaultWindow::setWidth(uint newWidth) noexcept {
  int width;
  int height;

  SDL_GetWindowSize(this->window, &width, &height);
  SDL_SetWindowSize(this->window, (int)newWidth, height);
}

void DefaultWindow::setHeight(uint newHeight) noexcept {
  int width;
  int height;

  SDL_GetWindowSize(this->window, &width, &height);
  SDL_SetWindowSize(this->window, width, (int)newHeight);
}

glm::ivec2 DefaultWindow::getGeometry() noexcept {
  glm::ivec2 geometry;

  SDL_GetWindowSize(this->window, &geometry.x, &geometry.y);
  return geometry;
}

void DefaultWindow::setGeometry(const glm::ivec2 &geometry) noexcept {
  SDL_SetWindowSize(this->window, geometry.x, geometry.y);
}

float DefaultWindow::getAspect() noexcept {
  const glm::ivec2 geometry = this->getGeometry();
  return (float)geometry.x / (float)geometry.y;
}

void DefaultWindow::setPositionX(int posX) noexcept {
  int x;
  int y;

  SDL_GetWindowPosition(this->window, &x, &y);
  SDL_SetWindowPosition(this->window, posX, y);
}

void DefaultWindow::setPositionY(int posY) noexcept {
  int x;
  int y;

  SDL_GetWindowPosition(this->window, &x, &y);
  SDL_SetWindowPosition(this->window, x, posY);
}

glm::ivec2 DefaultWindow::getPosition() noexcept {
  glm::ivec2 position;

  SDL_GetWindowPosition(this->window, &position.x, &position.y);
  return position;
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

void DefaultWindow::setVsync(bool isVsync) noexcept {
  SDL_GL_SetSwapInterval(isVsync ? 1 : 0);
}

void DefaultWindow::setDoubleBuffering(bool isDoubleBuffering) {
  VAN_ENGINE_ERROR(
      "Cannot change double buffering within SDL2 implementation.");
}

void DefaultWindow::setType(WindowType newType) noexcept {
  if (newType == WindowType::Resizable) {
    SDL_SetWindowFullscreen(this->window, SDL_FALSE);
    SDL_SetWindowBordered(this->window, SDL_TRUE);
    SDL_SetWindowResizable(this->window, SDL_TRUE);
  } else if (newType == WindowType::Fullscreen) {
    SDL_SetWindowFullscreen(this->window, SDL_TRUE);
    SDL_SetWindowBordered(this->window, SDL_TRUE);
    SDL_SetWindowResizable(this->window, SDL_FALSE);
  } else if (newType == WindowType::Borderless) {
    SDL_SetWindowFullscreen(this->window, SDL_FALSE);
    SDL_SetWindowBordered(this->window, SDL_FALSE);
    SDL_SetWindowResizable(this->window, SDL_FALSE);
  } else {
    SDL_SetWindowFullscreen(this->window, SDL_FALSE);
    SDL_SetWindowBordered(this->window, SDL_TRUE);
    SDL_SetWindowResizable(this->window, SDL_FALSE);
  }

  this->windowType = newType;
}

WindowType DefaultWindow::getType() noexcept { return this->windowType; }

bool DefaultWindow::isDoubleBuffering() noexcept { return true; }

void DefaultWindow::swapBuffer() {
}

}  // namespace Vanadium
