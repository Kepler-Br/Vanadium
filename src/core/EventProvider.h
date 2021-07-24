#ifndef VANADIUM_EVENTPROVIDER_H
#define VANADIUM_EVENTPROVIDER_H

#include <functional>

#include "KeyCodes.h"
#include "Window.h"
#include "event/Event.h"

namespace vanadium {

class UserEndEventProvider {
  using EventCallback = std::function<void(Event *)>;

 public:
  [[nodiscard]] virtual bool isKeyPressed(
      keyboard::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isKeyReleased(
      keyboard::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isKeyJustPressed(
      keyboard::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isKeyJustReleased(
      keyboard::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isMousePressed(
      mouse::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isMouseReleased(
      mouse::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isMouseJustPressed(
      mouse::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual bool isMouseJustReleased(
      mouse::KeyCode keycode) const noexcept = 0;
  [[nodiscard]] virtual glm::ivec2 getMouseDelta() const noexcept = 0;
  [[nodiscard]] virtual glm::ivec2 getMousePosition() const noexcept = 0;
  virtual void setEventCallback(EventCallback eventCallback) noexcept = 0;
};

class EventProvider : public UserEndEventProvider {
 protected:
  using EventCallback = std::function<void(Event *)>;

  Window *_window;
  EventCallback _eventCallback;
  //    bool dispatchEventsImmediately = true;

 public:
  explicit EventProvider(Window *window) : _window(window) {}
  virtual ~EventProvider() = default;

  virtual void update() noexcept = 0;
  virtual void dispatch() noexcept = 0;
  //    virtual void setDispatchImmediately(bool isDispatchingImmediately)
  //    noexcept { this->dispatchEventsImmediately = isDispatchingImmediately; }
  void setEventCallback(EventCallback eventCallback) noexcept override {
    this->_eventCallback = eventCallback;
  }
};

class EventProviderFactory {
 public:
  static EventProvider *create(Window *window);
};

}  // namespace vanadium
#endif  // VANADIUM_EVENTPROVIDER_H
