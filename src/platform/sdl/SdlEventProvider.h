#ifndef VANADIUM_PLATFORM_SDLEVENTPROVIDER_H
#define VANADIUM_PLATFORM_SDLEVENTPROVIDER_H

#include <vector>

#include "../../core/EventProvider.h"

namespace vanadium {
class Window;
class Event;

// Todo: implement dispatch immediately.
class SdlEventProvider : public EventProvider {
 private:
  glm::ivec2 _mouseDelta = {0, 0};
  glm::ivec2 _mousePrevPosition = {0, 0};
  glm::ivec2 _mousePosition = {0, 0};
  uint32_t _mouseButtonMask = 0;
  uint32_t _prevMouseButtonMask = 0;

  uint8_t *_previousKeyState = nullptr;
  const uint8_t *_currentKeyState = nullptr;

  std::vector<Event *> _eventQueue;

 public:
  explicit SdlEventProvider();
  ~SdlEventProvider() override;

  void update() noexcept override;
  void dispatch() noexcept override;

  [[nodiscard]] bool isKeyPressed(
      keyboard::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isKeyReleased(
      keyboard::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isKeyJustPressed(
      keyboard::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isKeyJustReleased(
      keyboard::KeyCode keycode) const noexcept override;

  [[nodiscard]] bool isMousePressed(
      mouse::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isMouseReleased(
      mouse::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isMouseJustPressed(
      mouse::KeyCode keycode) const noexcept override;
  [[nodiscard]] bool isMouseJustReleased(
      mouse::KeyCode keycode) const noexcept override;

  [[nodiscard]] glm::ivec2 getMouseDelta() const noexcept override;
  [[nodiscard]] glm::ivec2 getMousePosition() const noexcept override;
};

}  // namespace vanadium

#endif  // VANADIUM_PLATFORM_SDLEVENTPROVIDER_H
