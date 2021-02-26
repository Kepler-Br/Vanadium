#ifndef VANADIUM_WINDOWEVENT_H
#define VANADIUM_WINDOWEVENT_H

#include <glm/vec2.hpp>
#include "Event.h"
#include "../core/Types.h"

namespace Vanadium
{

class WindowResizeEvent: public Event
{
private:
    VNsize newWidth;
    VNsize newHeight;

public:
    WindowResizeEvent(VNsize newWidth, VNsize newHeight):
        newWidth(newWidth),
        newHeight(newHeight)
    {}
    WindowResizeEvent(const glm::ivec2 &newGeometry):
        newWidth(newGeometry.x),
        newHeight(newGeometry.y)
    {}

    VNsize getWidth() const noexcept { return this->newWidth; }
    VNsize getHeight() const noexcept { return this->newHeight; }
    glm::ivec2 getNewGeometry() const noexcept { return {this->newWidth, this->newHeight}; }
    EventType getType() const noexcept override { return EventType::WindowResized; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "WindowResizedEvent: (" << this->newWidth << " " << this->newHeight << ")";
        return ss.str();
    }
};

class WindowResizeStopEvent: public Event
{
private:
    VNsize newWidth;
    VNsize newHeight;

public:
    WindowResizeStopEvent(VNsize newWidth, VNsize newHeight):
        newWidth(newWidth),
        newHeight(newHeight)
    {}
    WindowResizeStopEvent(const glm::ivec2 &newGeometry):
        newWidth(newGeometry.x),
        newHeight(newGeometry.y)
    {}

    VNsize getWidth() const noexcept { return this->newWidth; }
    VNsize getHeight() const noexcept { return this->newHeight; }
    glm::ivec2 getNewGeometry() const noexcept { return {this->newWidth, this->newHeight}; }
    EventType getType() const noexcept override { return EventType::WindowResizeStop; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "WindowResizedEvent: (" << this->newWidth << " " << this->newHeight << ")";
        return ss.str();
    }
};

class WindowCloseEvent: public Event
{
public:
    WindowCloseEvent() = default;

    EventType getType() const noexcept override { return EventType::WindowClose; }
    std::string toString() const noexcept override { return "WindowCloseEvent"; }
};

}
#endif //VANADIUM_WINDOWEVENT_H
