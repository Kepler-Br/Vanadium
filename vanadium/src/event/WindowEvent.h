#ifndef VANADIUM_WINDOWEVENT_H
#define VANADIUM_WINDOWEVENT_H

#include <glm/vec2.hpp>
#include "Event.h"
#include "../core/Types.h"
#include <sstream>

namespace Vanadium
{

class WindowSizeChangedEvent: public Event
{
private:
    VNsize newWidth;
    VNsize newHeight;

public:
    WindowSizeChangedEvent(VNsize newWidth, VNsize newHeight):
        newWidth(newWidth),
        newHeight(newHeight)
    {}

    VNsize getWidth() const noexcept { return this->newWidth; }
    VNsize getHeight() const noexcept { return this->newHeight; }
    glm::ivec2 getNewGeometry() const noexcept { return {this->newWidth, this->newHeight}; }
    Event::Type getType() const noexcept override { return Event::Type::WindowSizeChanged; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "WindowSizeChangedEvent: (" << this->newWidth << ", " << this->newHeight << ")";
        return ss.str();
    }
};

class WindowCloseEvent: public Event
{
public:
    WindowCloseEvent() = default;

    Event::Type getType() const noexcept override { return Event::Type::WindowClose; }
    std::string toString() const noexcept override { return "WindowCloseEvent"; }
};

class WindowFocusLostEvent: public Event
{
public:
    WindowFocusLostEvent() = default;

    Event::Type getType() const noexcept override { return Event::Type::WindowLostFocus; }
    std::string toString() const noexcept override { return "WindowFocusLostEvent"; }
};

class WindowFocusGainEvent: public Event
{
public:
    WindowFocusGainEvent() = default;

    Event::Type getType() const noexcept override { return Event::Type::WindowGainFocus; }
    std::string toString() const noexcept override { return "WindowFocusGainEvent"; }
};

}
#endif //VANADIUM_WINDOWEVENT_H
