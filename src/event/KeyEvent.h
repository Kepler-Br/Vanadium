#ifndef VANADIUM_KEYEVENT_H
#define VANADIUM_KEYEVENT_H

#include <sstream>
#include <string>

#include "../core/KeyCodes.h"
#include "Event.h"

namespace vanadium {

class KeyEvent : public Event {
 protected:
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
  explicit KeyPressedEvent(keyboard::KeyCode keycode, void *raw = nullptr,
                           size_t rawSize = 0)
      : KeyEvent(keycode, raw, rawSize) {}
  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::KeyPressed;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    std::string asString =
        fmt::format("KeyPressedEvent: {} ({})", (uint16_t)this->_keycode,
                    keyboard::toString(this->_keycode));

    return asString;
  }
};

class KeyReleasedEvent : public KeyEvent {
 public:
  explicit KeyReleasedEvent(keyboard::KeyCode keycode, void *raw = nullptr,
                            size_t rawSize = 0)
      : KeyEvent(keycode, raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::KeyReleased;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    std::string asString =
        fmt::format("KeyReleasedEvent: {} ({})", (uint16_t)this->_keycode,
                    keyboard::toString(this->_keycode));

    return asString;
  }
};

}  // namespace vanadium

#endif  // VANADIUM_KEYEVENT_H
