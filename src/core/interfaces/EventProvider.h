#pragma once

#include <functional>

namespace vanadium {

class Event;

namespace keyboard {
enum class KeyCode;
}

namespace mouse {
enum class KeyCode;
}

using EventCallback = std::function<void(Event *)>;

class EventProvider {
 public:
  virtual ~EventProvider() = default;

  [[nodiscard]] virtual bool isKeyPressed(keyboard::KeyCode keycode) const = 0;
  [[nodiscard]] virtual bool isKeyReleased(keyboard::KeyCode keycode) const = 0;
  [[nodiscard]] virtual bool isKeyJustPressed(
      keyboard::KeyCode keycode) const = 0;
  [[nodiscard]] virtual bool isKeyJustReleased(
      keyboard::KeyCode keycode) const = 0;

  [[nodiscard]] virtual bool isMousePressed(mouse::KeyCode keycode) const = 0;
  [[nodiscard]] virtual bool isMouseReleased(mouse::KeyCode keycode) const = 0;
  [[nodiscard]] virtual bool isMouseJustPressed(
      mouse::KeyCode keycode) const = 0;
  [[nodiscard]] virtual bool isMouseJustReleased(
      mouse::KeyCode keycode) const = 0;

  [[nodiscard]] virtual glm::ivec2 getMouseDelta() const = 0;
  [[nodiscard]] virtual glm::ivec2 getMousePosition() const = 0;

  virtual void setEventCallback(const EventCallback &eventCallback) = 0;
};

class EngineEndEventProvider : public EventProvider {
 public:
  ~EngineEndEventProvider() override = default;

  virtual void update() = 0;
  virtual void dispatch() = 0;
};

}  // namespace vanadium
