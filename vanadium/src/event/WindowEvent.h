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
    WindowSizeChangedEvent(VNsize newWidth, VNsize newHeight, void *raw = nullptr, VNsize rawSize = 0):
        Event(raw, rawSize),
        newWidth(newWidth),
        newHeight(newHeight)
    {}

    [[nodiscard]]
    VNsize getWidth() const noexcept { return this->newWidth; }
    [[nodiscard]]
    VNsize getHeight() const noexcept { return this->newHeight; }
    [[nodiscard]]
    glm::ivec2 getNewGeometry() const noexcept { return {this->newWidth, this->newHeight}; }
    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::WindowSizeChanged; }
    [[nodiscard]]
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
    WindowCloseEvent(void *raw = nullptr, VNsize rawSize = 0):
        Event(raw, rawSize)
    {}

    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::WindowClose; }
    [[nodiscard]]
    std::string toString() const noexcept override { return "WindowCloseEvent"; }
};

class WindowFocusLostEvent: public Event
{
public:
    WindowFocusLostEvent(void *raw = nullptr, VNsize rawSize = 0):
            Event(raw, rawSize)
    {}

    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::WindowLostFocus; }
    [[nodiscard]]
    std::string toString() const noexcept override { return "WindowFocusLostEvent"; }
};

class WindowFocusGainEvent: public Event
{
public:
    WindowFocusGainEvent(void *raw = nullptr, VNsize rawSize = 0):
        Event(raw, rawSize)
    {}

    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::WindowGainFocus; }
    [[nodiscard]]
    std::string toString() const noexcept override { return "WindowFocusGainEvent"; }
};

}
#endif //VANADIUM_WINDOWEVENT_H
