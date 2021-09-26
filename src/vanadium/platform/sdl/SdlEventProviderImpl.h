#pragma once

#include <glm/vec2.hpp>
#include <vector>

#include "vanadium/core/interfaces/EventProvider.h"
#include "vanadium/core/types/KeyboardKeyCode.h"
#include "vanadium/core/types/MouseKeyCode.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class Event;

class SdlEventProviderImpl : public EngineEndEventProvider {
 private:
  Ref<EventDispatcher> _dispatcher = nullptr;

  glm::ivec2 _mouseDelta = {0, 0};
  glm::ivec2 _mousePrevPosition = {0, 0};
  glm::ivec2 _mousePosition = {0, 0};
  uint32_t _mouseButtonMask = 0;
  uint32_t _prevMouseButtonMask = 0;

  uint8_t *_previousKeyState = nullptr;
  const uint8_t *_currentKeyState = nullptr;

  std::vector<Event *> _eventQueue;

 public:
  explicit SdlEventProviderImpl();
  ~SdlEventProviderImpl() override;

#pragma region EventProvider

  [[nodiscard]] bool isKeyPressed(keyboard::KeyCode keycode) const override;
  [[nodiscard]] bool isKeyReleased(keyboard::KeyCode keycode) const override;
  [[nodiscard]] bool isKeyJustPressed(keyboard::KeyCode keycode) const override;
  [[nodiscard]] bool isKeyJustReleased(
      keyboard::KeyCode keycode) const override;

  [[nodiscard]] bool isMousePressed(mouse::KeyCode keycode) const override;
  [[nodiscard]] bool isMouseReleased(mouse::KeyCode keycode) const override;
  [[nodiscard]] bool isMouseJustPressed(mouse::KeyCode keycode) const override;
  [[nodiscard]] bool isMouseJustReleased(mouse::KeyCode keycode) const override;

  [[nodiscard]] glm::ivec2 getMouseDelta() const override;
  [[nodiscard]] glm::ivec2 getMousePosition() const override;

  void setDispatcher(Ref<EventDispatcher> dispatcher) override;

#pragma endregion

#pragma region EngineEndEventProvider

  void update() override;
  void dispatch() override;

#pragma endregion
};

}  // namespace vanadium
