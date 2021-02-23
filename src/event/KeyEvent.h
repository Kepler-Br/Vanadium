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
private:
    KeyCode keycode;

public:
    explicit KeyEvent(KeyCode keycode):
        keycode(keycode)
    {}

    KeyCode getKeyCode() const noexcept { return this->keycode; }
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(KeyCode keycode):
        KeyEvent(keycode)
    {}

    EventType getType() const noexcept override { return EventType::KeyPressed; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "KeyPressedEvent: " << (uint16_t)this->getKeyCode();
        return ss.str();
    }
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(KeyCode keycode):
        KeyEvent(keycode)
    {}

    EventType getType() const noexcept override { return EventType::KeyReleased; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "KeyReleasedEvent: " << (uint16_t)this->getKeyCode();
        return ss.str();
    }
};

}
#endif //VANADIUM_KEYEVENT_H
