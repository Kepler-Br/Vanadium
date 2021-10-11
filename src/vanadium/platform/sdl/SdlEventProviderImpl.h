#pragma once

#include <SDL_scancode.h>

#include <array>
#include <glm/vec2.hpp>
#include <vector>

#include "vanadium/core/interfaces/constructed/EventProvider.h"
#include "vanadium/core/interfaces/constructed/factories/LoggerFactory.h"
#include "vanadium/core/types/KeyboardKeyCode.h"
#include "vanadium/core/types/MouseKeyCode.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class Event;

class SdlEventProviderImpl : public EngineEndEventProvider {
 private:
  Ref<EventDispatcher> _dispatcher = nullptr;
  Ref<Logger> _logger = nullptr;

  glm::ivec2 _mouseDelta = {0, 0};
  glm::ivec2 _mousePrevPosition = {0, 0};
  glm::ivec2 _mousePosition = {0, 0};
  uint32_t _mouseButtonMask = 0;
  uint32_t _prevMouseButtonMask = 0;

  UniqueRef<std::array<uint8_t, SDL_NUM_SCANCODES>> _previousKeyState = nullptr;

  const uint8_t *_currentKeyState = nullptr;

  std::vector<Event *> _eventQueue;

 public:
  explicit SdlEventProviderImpl(Ref<LoggerFactory> loggerFactory);
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
