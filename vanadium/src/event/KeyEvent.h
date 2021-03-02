#ifndef VANADIUM_KEYEVENT_H
#define VANADIUM_KEYEVENT_H

#include <sstream>
#include <string>
#include "Event.h"
#include "../core/KeyCodes.h"

namespace Vanadium
{

class KeyEvent : public Event
{
protected:
    Keyboard::KeyCode keycode;

public:
    explicit KeyEvent(Keyboard::KeyCode keycode):
        keycode(keycode)
    {}

    [[nodiscard]]
    Keyboard::KeyCode getKeyCode() const noexcept { return this->keycode; }
};

class KeyPressedEvent : public KeyEvent
{
public:
    explicit KeyPressedEvent(Keyboard::KeyCode keycode):
        KeyEvent(keycode)
    {}
    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::KeyPressed; }
    [[nodiscard]]
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "KeyPressedEvent: " << (uint16_t)this->keycode;
        ss << " (" << Keyboard::toString(this->keycode) << ")";
        return ss.str();
    }
};

class KeyReleasedEvent : public KeyEvent
{
public:
    explicit KeyReleasedEvent(Keyboard::KeyCode keycode):
        KeyEvent(keycode)
    {}

    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::KeyReleased; }
    [[nodiscard]]
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "KeyReleasedEvent: " << (uint16_t)this->keycode;
        ss << " (" << Keyboard::toString(this->keycode) << ")";
        return ss.str();
    }
};

}
#endif //VANADIUM_KEYEVENT_H
