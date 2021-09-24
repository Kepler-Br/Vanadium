#pragma once

#include "core/Types.h"
#include "window/WindowProperties.h"

namespace vanadium {

class Window {
 public:
  virtual ~Window() = default;

  virtual void setTitle(const std::string &title) noexcept = 0;
  [[nodiscard]] virtual const std::string &getTitle() const noexcept = 0;
  // Geometry.
  virtual void setWidth(unsigned int width) noexcept = 0;
  virtual void setHeight(unsigned int width) noexcept = 0;
  [[nodiscard]] virtual const glm::ivec2 getGeometry() const noexcept = 0;
  virtual void setGeometry(const glm::ivec2 &geometry) noexcept = 0;
  [[nodiscard]] virtual float getAspect() const noexcept = 0;
  // Position.
  virtual void setPositionX(int posX) noexcept = 0;
  virtual void setPositionY(int posY) noexcept = 0;
  [[nodiscard]] virtual const glm::ivec2 getPosition() const noexcept = 0;
  virtual void setPosition(const glm::ivec2 &position) = 0;

  virtual void grabCursor(bool isCursorGrabbed) noexcept = 0;
  virtual bool isCursorGrabbed() noexcept = 0;
  [[nodiscard]] virtual void *getRaw() const noexcept = 0;
  virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
  [[nodiscard]] virtual bool isDoubleBuffering() const noexcept = 0;
  virtual void setType(WindowType newType) noexcept = 0;
  [[nodiscard]] virtual WindowType getType() const noexcept = 0;
  virtual void swapBuffer() = 0;
  [[nodiscard]] virtual void *getNativeDisplayType() const noexcept = 0;
  [[nodiscard]] virtual void *getNativeWindowHandle() const noexcept = 0;

  static Ref<Window> create(const WindowProperties &properties);
};

}  // namespace vanadium
