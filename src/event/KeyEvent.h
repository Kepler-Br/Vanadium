#ifndef VANADIUM_KEYEVENT_H
#define VANADIUM_KEYEVENT_H

#include <sstream>
#include <string>

#include "../core/KeyCodes.h"
#include "Event.h"

namespace Vanadium {

class KeyEvent : public Event {
 protected:
  Keyboard::KeyCode keycode;
  char *raw = nullptr;

 public:
  explicit KeyEvent(Keyboard::KeyCode keycode, void *raw = nullptr,
                    VNsize rawSize = 0)
      : Event(raw, rawSize), keycode(keycode) {}

  ~KeyEvent() override { delete[] this->raw; }
  [[nodiscard]] Keyboard::KeyCode getKeyCode() const noexcept {
    return this->keycode;
  }
};

class KeyPressedEvent : public KeyEvent {
 public:
  explicit KeyPressedEvent(Keyboard::KeyCode keycode, void *raw = nullptr,
                           VNsize rawSize = 0)
      : KeyEvent(keycode, raw, rawSize) {}
  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::KeyPressed;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;

    ss << "KeyPressedEvent: " << (uint16_t)this->keycode;
    ss << " (" << Keyboard::toString(this->keycode) << ")";
    return ss.str();
  }
};

class KeyReleasedEvent : public KeyEvent {
 public:
  explicit KeyReleasedEvent(Keyboard::KeyCode keycode, void *raw = nullptr,
                            VNsize rawSize = 0)
      : KeyEvent(keycode, raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::KeyReleased;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;

    ss << "KeyReleasedEvent: " << (uint16_t)this->keycode;
    ss << " (" << Keyboard::toString(this->keycode) << ")";
    return ss.str();
  }
};

}  // namespace Vanadium
#endif  // VANADIUM_KEYEVENT_H
