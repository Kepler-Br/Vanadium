#ifndef VANADIUM_EVENT_H
#define VANADIUM_EVENT_H

#include <string>
#include "../core/Assert.h"

namespace Vanadium
{

//enum EventCategory
//{
//    EventCategoryNone           = 0,
//    EventCategoryKey            = 1 << 0,
//    EventCategoryMouse          = 1 << 1,
//    EventCategoryMouseButton    = 1 << 2,
//    EventCategoryWindow         = 1 << 3,
//};

class Event
{
public:
    enum class Type
    {
        KeyPressed = 0,
        KeyReleased,
        MouseMove,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseScroll,
        WindowSizeChanged,
        WindowClose,
        WindowLostFocus,
        WindowGainFocus,
    };
private:
    bool handled = false;

public:
    virtual Event::Type getType() const noexcept = 0 ;
    virtual std::string toString() const noexcept = 0;
    bool isHandled() const noexcept { return this->handled; }
    void setAsHandled() noexcept { this->handled = true; }

    static std::string typeToString(Event::Type type) noexcept
    {
        switch (type)
        {
            case Event::Type::KeyPressed:
                return "KeyPressed";
            case Event::Type::KeyReleased:
                return "KeyReleased";
            case Event::Type::MouseMove:
                return "MouseMove";
            case Event::Type::MouseButtonPressed:
                return "MouseButtonPressed";
            case Event::Type::MouseButtonReleased:
                return "MouseButtonReleased";
            case Event::Type::MouseScroll:
                return "MouseScroll";
            case Event::Type::WindowSizeChanged:
                return "WindowSizeChanged";
            case Event::Type::WindowClose:
                return "WindowClose";
        }
        VAN_ENGINE_ASSERT(false, "Unknown event type!");
        return 0;
    }
};

}

#endif //VANADIUM_EVENT_H
