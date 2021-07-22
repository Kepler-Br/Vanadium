#ifndef VANADIUM_WINDOW_H
#define VANADIUM_WINDOW_H

#include <glm/vec2.hpp>
#include <string>

#include "../event/Event.h"
#include "Types.h"

namespace vanadium {

enum class WindowType { None = 0, Fullscreen, Resizable, Borderless, Normal };

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
  //  struct Properties {
  //    Properties(VNsize width, VNsize height) : width(width), height(height)
  //    {} Properties() = default;
  //
  //    VNsize width = 0, height = 0;
  //    std::string title = "Vanadium SDL2";
  //    bool vSync = true;
  //    bool doubleBuffering = true;
  //    bool resizable = false;
  //    bool borderless = false;
  //    bool fullscreen = false;
  //    bool invisible = false;
  //  };

 public:
  virtual ~Window() = default;

  virtual void setTitle(const std::string &title) noexcept = 0;
  virtual std::string getTitle() noexcept = 0;
  // Geometry.
  virtual void setWidth(uint width) noexcept = 0;
  virtual void setHeight(uint width) noexcept = 0;
  virtual glm::ivec2 getGeometry() noexcept = 0;
  virtual void setGeometry(const glm::ivec2 &geometry) noexcept = 0;
  virtual float getAspect() noexcept = 0;
  // Position.
  virtual void setPositionX(int posX) noexcept = 0;
  virtual void setPositionY(int posY) noexcept = 0;
  virtual glm::ivec2 getPosition() noexcept = 0;
  virtual void setPosition(const glm::ivec2 &position) = 0;

  virtual void grabCursor(bool isCursorGrabbed) noexcept = 0;
  virtual bool isCursorGrabbed() noexcept = 0;
  virtual void *getRaw() noexcept = 0;
  virtual void setVsync(bool isVsync) noexcept = 0;
  virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
  virtual bool isDoubleBuffering() noexcept = 0;
  virtual void setType(WindowType newType) noexcept = 0;
  virtual WindowType getType() noexcept = 0;
  virtual void swapBuffer() = 0;

  static Window *create(const WindowProperties &properties);
};

}  // namespace Vanadium
#endif  // VANADIUM_WINDOW_H
