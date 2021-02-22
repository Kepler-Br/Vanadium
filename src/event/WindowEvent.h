#ifndef VANADIUM_WINDOWEVENT_H
#define VANADIUM_WINDOWEVENT_H

#include "Event.h"
#include <glm/vec2.hpp>

namespace Van
{

class WindowResizeEvent: public Event
{
private:
    uint32_t newWidth;
    uint32_t newHeight;

public:
    WindowResizeEvent(uint32_t newWidth, uint32_t newHeight):
        newWidth(newWidth),
        newHeight(newHeight)
    {}
    WindowResizeEvent(const glm::ivec2 &newGeometry):
        newWidth(newGeometry.x),
        newHeight(newGeometry.y)
    {}

    uint32_t getWidth() const noexcept { return this->newWidth; }
    uint32_t getHeight() const noexcept { return this->newHeight; }
    glm::ivec2 getNewGeometry() const noexcept { return {this->newWidth, this->newHeight}; }
    EventType getType() const noexcept override { return EventType::WindowResized; }
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
