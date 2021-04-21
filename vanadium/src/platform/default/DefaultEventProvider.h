#ifndef VANADIUM_DEFAULTEVENTPROVIDER_H
#define VANADIUM_DEFAULTEVENTPROVIDER_H

#include <vector>

#include "../../core/EventProvider.h"
//#include "../../core/Window.h"

namespace Vanadium {
class Window;
class Event;

// Todo: implement dispatch immediately.
class DefaultEventProvider : public EventProvider {
 private:
  glm::ivec2 mouseDelta = {0, 0};
  glm::ivec2 mousePrevPosition = {0, 0};
  glm::ivec2 mousePosition = {0, 0};
  uint32_t mouseButtonMask = 0;
  uint32_t prevMouseButtonMask = 0;

  uint8_t *previousKeyState = nullptr;
  const uint8_t *currentKeyState = nullptr;

  std::vector<Event *> eventQueue;

 public:
  explicit DefaultEventProvider(Window *window);
  ~DefaultEventProvider() override;

  void update() noexcept override;
  void dispatch() noexcept override;

  [[nodiscard]] bool isKeyPressed(
      Keyboard::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isKeyReleased(
      Keyboard::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isKeyJustPressed(
      Keyboard::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isKeyJustReleased(
      Keyboard::KeyCode keycode) const noexcept override;

  [[nodiscard]] bool isMousePressed(
      Mouse::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isMouseReleased(
      Mouse::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isMouseJustPressed(
      Mouse::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isMouseJustReleased(
      Mouse::KeyCode keycode) const noexcept override;

  [[nodiscard]] glm::ivec2 getMouseDelta() const noexcept override;
  [[nodiscard]] glm::ivec2 getMousePosition() const noexcept override;
};

}  // namespace Vanadium

#endif  // VANADIUM_DEFAULTEVENTPROVIDER_H
