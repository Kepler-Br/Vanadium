#include "SdlWindowImpl.h"

#include <SDL_syswm.h>
#include <fmt/format.h>

#include "core/Exceptions.h"

namespace vanadium {

void SdlWindowImpl::init(const WindowProperties &properties) {
  Uint32 windowFlags = 0x0;

  this->_wmi = MakeUnique<SDL_SysWMinfo>();

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
    this->_logger->error(message);

    throw InitializationInterrupted(message);
  }

  SDL_VERSION(&this->_wmi->version);

  if (!SDL_GetWindowWMInfo(this->_window, this->_wmi.get())) {
    throw InitializationInterrupted("Cannot get SDL2 window info.");
  }
}

SdlWindowImpl::SdlWindowImpl(const WindowProperties &properties,
                             Ref<Logger> logger)
    : _logger(std::move(logger)),
      _title(properties.getTitle()),
      _windowType(properties.getType()) {
  this->_logger->trace(
      fmt::format("Creating SDL2 window with title \"{}\".", this->_title));

  this->init(properties);
}

SdlWindowImpl::~SdlWindowImpl() {
  this->_logger->trace(
      fmt::format("Destroying SDL2 window with title \"{}\".", this->_title));

  SDL_DestroyWindow(this->_window);
}

void SdlWindowImpl::setTitle(const std::string &newTitle) noexcept {
  SDL_SetWindowTitle(this->_window, _title.c_str());
  this->_title = newTitle;
}

const std::string &SdlWindowImpl::getTitle() const noexcept {
  return this->_title;
}

void SdlWindowImpl::setWidth(unsigned int newWidth) noexcept {
  int width;
  int height;

  SDL_GetWindowSize(this->_window, &width, &height);
  SDL_SetWindowSize(this->_window, (int)newWidth, height);
}

void SdlWindowImpl::setHeight(unsigned int newHeight) noexcept {
  int width;
  int height;

  SDL_GetWindowSize(this->_window, &width, &height);
  SDL_SetWindowSize(this->_window, width, (int)newHeight);
}

glm::ivec2 SdlWindowImpl::getGeometry() const noexcept {
  glm::ivec2 geometry;

  SDL_GetWindowSize(this->_window, &geometry.x, &geometry.y);
  return geometry;
}

void SdlWindowImpl::setGeometry(const glm::ivec2 &geometry) noexcept {
  SDL_SetWindowSize(this->_window, geometry.x, geometry.y);
}

float SdlWindowImpl::getAspect() const noexcept {
  const glm::ivec2 geometry = this->getGeometry();
  return (float)geometry.x / (float)geometry.y;
}

void SdlWindowImpl::setPositionX(int posX) noexcept {
  int x;
  int y;

  SDL_GetWindowPosition(this->_window, &x, &y);
  SDL_SetWindowPosition(this->_window, posX, y);
}

void SdlWindowImpl::setPositionY(int posY) noexcept {
  int x;
  int y;

  SDL_GetWindowPosition(this->_window, &x, &y);
  SDL_SetWindowPosition(this->_window, x, posY);
}

glm::ivec2 SdlWindowImpl::getPosition() const noexcept {
  glm::ivec2 position;

  SDL_GetWindowPosition(this->_window, &position.x, &position.y);
  return position;
}

void SdlWindowImpl::setPosition(const glm::ivec2 &position) {
  SDL_SetWindowPosition(this->_window, position.x, position.y);
}

void SdlWindowImpl::grabCursor(bool isCursorGrabbed) noexcept {
  SDL_SetRelativeMouseMode(isCursorGrabbed ? SDL_TRUE : SDL_FALSE);
}

bool SdlWindowImpl::isCursorGrabbed() noexcept {
  return SDL_GetRelativeMouseMode();
}

void *SdlWindowImpl::getRaw() const noexcept { return this->_window; }

void SdlWindowImpl::setDoubleBuffering(bool isDoubleBuffering) {
  // noop.
}

void SdlWindowImpl::setType(WindowType newType) noexcept {
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

WindowType SdlWindowImpl::getType() const noexcept { return this->_windowType; }

bool SdlWindowImpl::isDoubleBuffering() const noexcept { return true; }

void SdlWindowImpl::swapBuffer() {
  // noop.
}

void *SdlWindowImpl::getNativeDisplayType() const noexcept {
#if VANADIUM_PLATFORM_LINUX
  return this->_wmi->info.x11.display;
#elif VANADIUM_PLATFORM_MACOS
  return nullptr;
#elif VANADIUM_PLATFORM_WINDOWS
  return nullptr;
#endif
}

void *SdlWindowImpl::getNativeWindowHandle() const noexcept {
#if VANADIUM_PLATFORM_LINUX
  return (void *)this->_wmi->info.x11.window;
#elif VANADIUM_PLATFORM_MACOS
  return this->_wmi->info.cocoa.window;
#elif VANADIUM_PLATFORM_WINDOWS
  return this->_wmi->info.win.window;
#endif
}

}  // namespace vanadium
