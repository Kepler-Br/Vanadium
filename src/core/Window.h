#ifndef VANADIUM_WINDOW_H
#define VANADIUM_WINDOW_H

#include <glm/vec2.hpp>
#include <string>

#include "Types.h"
#include "event/Event.h"

namespace vanadium {

#pragma push_macro("None")
#undef None
enum class WindowType { None = 0, Fullscreen, Resizable, Borderless, Normal };
#pragma pop_macro("None")

enum class WindowState { Normal, Minimized, Maximized };

class WindowProperties {
 private:
  glm::ivec2 _geometry;
  std::optional<glm::ivec2> _position;
  std::string _title = "Vanadium:: window";
  WindowState _state = WindowState::Normal;
  WindowType _type = WindowType::Normal;
  bool _vsync = true;

 public:
  explicit WindowProperties(const glm::ivec2 &newGeometry)
      : _geometry(newGeometry) {}

  WindowProperties &withGeometry(const glm::ivec2 &newGeometry) {
    this->_geometry = newGeometry;
    return *this;
  }

  WindowProperties &withTitle(const std::string &newTitle) {
    this->_title = newTitle;
    return *this;
  }

  WindowProperties &withState(WindowState newState) {
    this->_state = newState;
    return *this;
  }

  WindowProperties &withType(WindowType newType) {
    this->_type = newType;
    return *this;
  }

  WindowProperties &withPosition(const glm::ivec2 &newPosition) {
    this->_position = newPosition;
    return *this;
  }

  WindowProperties &withVSync(bool newVsync) {
    this->_vsync = newVsync;
    return *this;
  }

  // Getters.
  [[nodiscard]] glm::ivec2 getGeometry() const { return this->_geometry; }
  [[nodiscard]] std::optional<glm::ivec2> getPosition() const {
    return this->_position;
  }
  [[nodiscard]] std::string getTitle() const { return this->_title; }
  [[nodiscard]] WindowState getState() const { return this->_state; }
  [[nodiscard]] WindowType getType() const { return this->_type; }
  [[nodiscard]] bool getVSync() const { return this->_vsync; }
};

class Window {
 public:
  virtual ~Window() = default;

  virtual void setTitle(const std::string &title) noexcept = 0;
  [[nodiscard]] virtual const std::string &getTitle() const noexcept = 0;
  // Geometry.
  virtual void setWidth(uint width) noexcept = 0;
  virtual void setHeight(uint width) noexcept = 0;
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
  virtual WindowType getType() const noexcept = 0;
  virtual void swapBuffer() = 0;
  [[nodiscard]] virtual void *getNativeDisplayType() const noexcept = 0;
  [[nodiscard]] virtual void *getNativeWindowHandle() const noexcept = 0;

  static Window *create(const WindowProperties &properties);
};

}  // namespace vanadium
#endif  // VANADIUM_WINDOW_H
