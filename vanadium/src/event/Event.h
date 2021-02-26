#ifndef VANADIUM_EVENT_H
#define VANADIUM_EVENT_H

#include <string>

namespace Vanadium {

enum class EventType
{
    KeyPressed = 0,
    KeyReleased,
    MouseMove,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScroll,
    WindowResized,
    WindowResizeStop,
    WindowClose,
};

enum EventCategory
{
    EventCategoryNone           = 0,
    EventCategoryKey            = 1 << 0,
    EventCategoryMouse          = 1 << 1,
    EventCategoryMouseButton    = 1 << 2,
    EventCategoryWindow         = 1 << 3,
};

class Event
{
private:
    bool handled = false;

public:
    virtual EventType getType() const noexcept = 0 ;
    virtual std::string toString() const noexcept = 0;
    bool isHandled() const noexcept { return this->handled; }
    void setAsHandled() noexcept { this->handled = true; }

};

}

#endif //VANADIUM_EVENT_H
