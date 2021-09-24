#pragma once

#include <sstream>
#include <string>

#include "Event.h"
#include "core/types/KeyboardKeyCode.h"

namespace vanadium {

class KeyEvent : public Event {
 private:
  keyboard::KeyCode _keycode;

 public:
  explicit KeyEvent(keyboard::KeyCode keycode, void *raw = nullptr,
                    size_t rawSize = 0)
      : Event(raw, rawSize), _keycode(keycode) {}

  ~KeyEvent() override = default;
  [[nodiscard]] keyboard::KeyCode getKeyCode() const noexcept {
    return this->_keycode;
  }
};

class KeyPressedEvent : public KeyEvent {
 public:
  using KeyEvent::KeyEvent;

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::KeyPressed;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    std::string asString =
        fmt::format("KeyPressedEvent: {} ({})", (uint16_t)this->getKeyCode(),
                    keyboard::toString(this->getKeyCode()));

    return asString;
  }
};

class KeyReleasedEvent : public KeyEvent {
 public:
  using KeyEvent::KeyEvent;

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::KeyReleased;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    std::string asString =
        fmt::format("KeyReleasedEvent: {} ({})", (uint16_t)this->getKeyCode(),
                    keyboard::toString(this->getKeyCode()));

    return asString;
  }
};

}  // namespace vanadium
