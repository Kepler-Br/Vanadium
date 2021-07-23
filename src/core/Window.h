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
 public:
  explicit WindowProperties(const glm::ivec2 &newGeometry)
      : geometry(newGeometry) {}

  WindowProperties &withGeometry(const glm::ivec2 &newGeometry) {
    this->geometry = newGeometry;
    return *this;
  }

  WindowProperties &withTitle(const std::string &newTitle) {
    this->title = newTitle;
    return *this;
  }

  WindowProperties &withState(WindowState newState) {
    this->state = newState;
    return *this;
  }

  WindowProperties &withType(WindowType newType) {
    this->type = newType;
    return *this;
  }

  WindowProperties &withPosition(const glm::ivec2 &newPosition) {
    this->position = newPosition;
    return *this;
  }

  WindowProperties &withVSync(bool newVsync) {
    this->vsync = newVsync;
    return *this;
  }

  // Getters.
  glm::ivec2 getGeometry() const { return this->geometry; }
  std::optional<glm::ivec2> getPosition() const { return this->position; }
  std::string getTitle() const { return this->title; }
  WindowState getState() const { return this->state; }
  WindowType getType() const { return this->type; }
  bool getVSync() const { return this->vsync; }

 private:
  glm::ivec2 geometry;
  std::optional<glm::ivec2> position;
  std::string title = "Vanadium:: window";
  WindowState state = WindowState::Normal;
  WindowType type = WindowType::Normal;
  bool vsync = true;
};

class Window {
 public:
  virtual ~Window() = default;

  virtual void setTitle(const std::string &title) noexcept = 0;
  virtual const std::string &getTitle() const noexcept = 0;
  // Geometry.
  virtual void setWidth(uint width) noexcept = 0;
  virtual void setHeight(uint width) noexcept = 0;
  virtual const glm::ivec2 getGeometry() const noexcept = 0;
  virtual void setGeometry(const glm::ivec2 &geometry) noexcept = 0;
  virtual float getAspect() const noexcept = 0;
  // Position.
  virtual void setPositionX(int posX) noexcept = 0;
  virtual void setPositionY(int posY) noexcept = 0;
  virtual const glm::ivec2 getPosition() const noexcept = 0;
  virtual void setPosition(const glm::ivec2 &position) = 0;

  virtual void grabCursor(bool isCursorGrabbed) noexcept = 0;
  virtual bool isCursorGrabbed() noexcept = 0;
  virtual void *getRaw() const noexcept = 0;
  virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
  virtual bool isDoubleBuffering() const noexcept = 0;
  virtual void setType(WindowType newType) noexcept = 0;
  virtual WindowType getType() const noexcept = 0;
  virtual void swapBuffer() = 0;
  virtual void *getNativeDisplayType() const noexcept = 0;
  virtual void *getNativeWindowHandle() const noexcept = 0;

  static Window *create(const WindowProperties &properties);
};

}  // namespace vanadium
#endif  // VANADIUM_WINDOW_H
