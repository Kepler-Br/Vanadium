#ifndef VANADIUM_MOUSEEVENT_H
#define VANADIUM_MOUSEEVENT_H

#include "Event.h"
#include "sstream"
#include <glm/vec2.hpp>
#include "../core/KeyCodes.h"

namespace Vanadium
{

class MouseMoveEvent : public Event
{
private:
    uint32_t newXPosition;
    uint32_t newYPosition;
    int32_t deltaX;
    int32_t deltaY;

public:
    MouseMoveEvent(uint32_t newXPosition, uint32_t newYPosition, int32_t deltaX, int32_t deltaY):
            newXPosition(newXPosition),
            newYPosition(newYPosition),
            deltaX(deltaX),
            deltaY(deltaY)
    {}
    EventType getType() const noexcept override { return EventType::MouseMove; }
    uint32_t getNewXPosition() const noexcept { return this->newXPosition; }
    uint32_t getNewYPosition() const noexcept { return this->newYPosition; }
    int32_t getDeltaX() const noexcept { return this->deltaX; }
    int32_t getDeltaY() const noexcept { return this->deltaY; }
    glm::ivec2 getNewPosition() const noexcept { return {this->newXPosition, this->newYPosition}; }
    glm::ivec2 getDelta() const noexcept { return {this->deltaX, this->deltaY}; }
};

class MouseScrollEvent: public Event
{
private:
    VNint verticalScroll;
    VNint horizontalScroll;

public:
    MouseScrollEvent(VNint vertical, VNint horizontal):
        verticalScroll(vertical),
        horizontalScroll(horizontal)
    {}

    VNint getVerticalScroll() const noexcept
    {
        return this->verticalScroll;
    }
    VNint getHorizontalScroll() const noexcept
    {
        return this->horizontalScroll;
    }
    EventType getType() const noexcept override { return EventType::MouseScroll; }
};

class MouseButtonEvent: public Event
{
private:
    uint16_t keycode;

public:
    explicit MouseButtonEvent(uint16_t keycode): keycode(keycode) {}
    uint16_t getKeyCode() const noexcept { return this->keycode; }
};

class MouseButtonPressedEvent: public MouseButtonEvent
{
public:
    explicit MouseButtonPressedEvent(uint16_t keycode): MouseButtonEvent(keycode) {}

    EventType getType() const noexcept override { return EventType::MouseButtonPressed; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "MouseButtonPressedEvent: " << (uint16_t)this->getKeyCode();
        return ss.str();
    }
};

class MouseButtonReleasedEvent: public MouseButtonEvent
{
public:
    explicit MouseButtonReleasedEvent(uint16_t keycode): MouseButtonEvent(keycode) {}

    EventType getType() const noexcept override { return EventType::MouseButtonReleased; }
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "MouseButtonReleased: " << (uint16_t)this->getKeyCode();
        return ss.str();
    }
};

}

#endif //VANADIUM_MOUSEEVENT_H
