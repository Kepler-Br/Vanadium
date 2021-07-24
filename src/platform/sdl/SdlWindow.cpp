#include "SdlWindow.h"

#include <SDL_syswm.h>
#include <bgfx/bgfx.h>

#include "core/Exceptions.h"
#include "core/Log.h"

namespace vanadium {

void SdlWindow::init(const WindowProperties &properties) {
  Uint32 windowFlags = 0x0;

  this->_wmi = new SDL_SysWMinfo;
  if (properties.getGeometry().x <= 0 || properties.getGeometry().y <= 0) {
    throw InitializationInterrupted("Window geometry is invalid!");
  }
  if (properties.getType() == WindowType::Borderless) {
    windowFlags |= SDL_WINDOW_BORDERLESS;
  } else if (this->_windowType == WindowType::Fullscreen) {
    windowFlags |= SDL_WINDOW_FULLSCREEN;
  } else if (this->_windowType == WindowType::Resizable) {
    windowFlags |= SDL_WINDOW_RESIZABLE;
  }
  std::optional<glm::ivec2> position = properties.getPosition();
  glm::ivec2 geometry = properties.getGeometry();

  this->_window = SDL_CreateWindow(
      this->_title.c_str(),
      position.has_value() ? position->x : SDL_WINDOWPOS_CENTERED,
      position.has_value() ? position->y : SDL_WINDOWPOS_CENTERED, geometry.x,
      geometry.y, windowFlags);
  if (this->_window == nullptr) {
    const std::string message =
        fmt::format("Cannot initialize SDL2 window: {}", SDL_GetError());
    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }
  SDL_VERSION(&this->_wmi->version);
  if (!SDL_GetWindowWMInfo(this->_window, this->_wmi)) {
    const std::string message = "Cannot get SDL2 window info.";
    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }
}

SdlWindow::SdlWindow(const WindowProperties &properties)
    : _title(properties.getTitle()), _windowType(properties.getType()) {
  VAN_ENGINE_TRACE("Creating SDL2 window.");
  this->init(properties);
}

SdlWindow::~SdlWindow() {
  VAN_ENGINE_TRACE("Destroying SDL2 window.");

  delete this->_wmi;
  SDL_DestroyWindow(this->_window);
}

void SdlWindow::setTitle(const std::string &newTitle) noexcept {
  SDL_SetWindowTitle(this->_window, _title.c_str());
  this->_title = newTitle;
}

const std::string &SdlWindow::getTitle() const noexcept { return this->_title; }

void SdlWindow::setWidth(uint newWidth) noexcept {
  int width;
  int height;

  SDL_GetWindowSize(this->_window, &width, &height);
  SDL_SetWindowSize(this->_window, (int)newWidth, height);
}

void SdlWindow::setHeight(uint newHeight) noexcept {
  int width;
  int height;

  SDL_GetWindowSize(this->_window, &width, &height);
  SDL_SetWindowSize(this->_window, width, (int)newHeight);
}

const glm::ivec2 SdlWindow::getGeometry() const noexcept {
  glm::ivec2 geometry;

  SDL_GetWindowSize(this->_window, &geometry.x, &geometry.y);
  return geometry;
}

void SdlWindow::setGeometry(const glm::ivec2 &geometry) noexcept {
  SDL_SetWindowSize(this->_window, geometry.x, geometry.y);
}

float SdlWindow::getAspect() const noexcept {
  const glm::ivec2 geometry = this->getGeometry();
  return (float)geometry.x / (float)geometry.y;
}

void SdlWindow::setPositionX(int posX) noexcept {
  int x;
  int y;

  SDL_GetWindowPosition(this->_window, &x, &y);
  SDL_SetWindowPosition(this->_window, posX, y);
}

void SdlWindow::setPositionY(int posY) noexcept {
  int x;
  int y;

  SDL_GetWindowPosition(this->_window, &x, &y);
  SDL_SetWindowPosition(this->_window, x, posY);
}

const glm::ivec2 SdlWindow::getPosition() const noexcept {
  glm::ivec2 position;

  SDL_GetWindowPosition(this->_window, &position.x, &position.y);
  return position;
}

void SdlWindow::setPosition(const glm::ivec2 &position) {
  SDL_SetWindowPosition(this->_window, position.x, position.y);
}

void SdlWindow::grabCursor(bool isCursorGrabbed) noexcept {
  SDL_SetRelativeMouseMode(isCursorGrabbed ? SDL_TRUE : SDL_FALSE);
}

bool SdlWindow::isCursorGrabbed() noexcept {
  return SDL_GetRelativeMouseMode();
}

void *SdlWindow::getRaw() const noexcept { return this->_window; }

void SdlWindow::setDoubleBuffering(bool isDoubleBuffering) {
  VAN_ENGINE_ERROR(
      "Cannot change double buffering within SDL2 implementation.");
}

void SdlWindow::setType(WindowType newType) noexcept {
  if (newType == WindowType::Resizable) {
    SDL_SetWindowFullscreen(this->_window, SDL_FALSE);
    SDL_SetWindowBordered(this->_window, SDL_TRUE);
    SDL_SetWindowResizable(this->_window, SDL_TRUE);
  } else if (newType == WindowType::Fullscreen) {
    SDL_SetWindowFullscreen(this->_window, SDL_TRUE);
    SDL_SetWindowBordered(this->_window, SDL_TRUE);
    SDL_SetWindowResizable(this->_window, SDL_FALSE);
  } else if (newType == WindowType::Borderless) {
    SDL_SetWindowFullscreen(this->_window, SDL_FALSE);
    SDL_SetWindowBordered(this->_window, SDL_FALSE);
    SDL_SetWindowResizable(this->_window, SDL_FALSE);
  } else {
    SDL_SetWindowFullscreen(this->_window, SDL_FALSE);
    SDL_SetWindowBordered(this->_window, SDL_TRUE);
    SDL_SetWindowResizable(this->_window, SDL_FALSE);
  }

  this->_windowType = newType;
}

WindowType SdlWindow::getType() const noexcept { return this->_windowType; }

bool SdlWindow::isDoubleBuffering() const noexcept { return true; }

void SdlWindow::swapBuffer() {}

void *SdlWindow::getNativeDisplayType() const noexcept {
#if VANADIUM_PLATFORM_LINUX
  return this->_wmi->info.x11.display;
#elif VANADIUM_PLATFORM_MACOS
  return nullptr;
#elif VANADIUM_PLATFORM_WINDOWS
  return nullptr;
#endif
}
void *SdlWindow::getNativeWindowHandle() const noexcept {
#if VANADIUM_PLATFORM_LINUX
  return (void *)this->_wmi->info.x11.window;
#elif VANADIUM_PLATFORM_MACOS
  return this->_wmi.info.cocoa.window;
#elif VANADIUM_PLATFORM_WINDOWS
  return this->_wmi.info.win.window;
#endif
}

}  // namespace vanadium
