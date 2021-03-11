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
    int32_t newXPosition;
    int32_t newYPosition;
    int32_t deltaX;
    int32_t deltaY;

public:
    MouseMoveEvent(int32_t newXPosition, int32_t newYPosition, int32_t deltaX, int32_t deltaY, void *raw = nullptr, VNsize rawSize = 0):
            Event(raw, rawSize),
            newXPosition(newXPosition),
            newYPosition(newYPosition),
            deltaX(deltaX),
            deltaY(deltaY)
    {}
    [[nodiscard]]
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "MouseMoveEvent. ";
        ss << "New position: (" << this->newXPosition << ", " << this->newYPosition << ");";
        ss << "Delta: (" << this->deltaX << ", " << this->deltaY << ");";
        return ss.str();
    }
    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::MouseMove; }
    [[nodiscard]]
    int32_t getNewXPosition() const noexcept { return this->newXPosition; }
    [[nodiscard]]
    int32_t getNewYPosition() const noexcept { return this->newYPosition; }
    [[nodiscard]]
    int32_t getDeltaX() const noexcept { return this->deltaX; }
    [[nodiscard]]
    int32_t getDeltaY() const noexcept { return this->deltaY; }
    [[nodiscard]]
    glm::ivec2 getNewPosition() const noexcept { return {this->newXPosition, this->newYPosition}; }
    [[nodiscard]]
    glm::ivec2 getDelta() const noexcept { return {this->deltaX, this->deltaY}; }
};

class MouseScrollEvent: public Event
{
private:
    VNint verticalScroll = 0;
    VNint horizontalScroll = 0;

public:
    MouseScrollEvent(VNint vertical, VNint horizontal, void *raw = nullptr, VNsize rawSize = 0):
        Event(raw, rawSize),
        verticalScroll(vertical),
        horizontalScroll(horizontal)
    {}
    [[nodiscard]]
    VNint getVerticalScroll() const noexcept
    {
        return this->verticalScroll;
    }
    [[nodiscard]]
    VNint getHorizontalScroll() const noexcept
    {
        return this->horizontalScroll;
    }
    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::MouseScroll; }
    [[nodiscard]]
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "MouseScrollEvent. ";
        ss << "Vertical: " << this->verticalScroll << "; ";
        ss << "Horizontal: " << this->horizontalScroll << ".";
        return ss.str();
    };
};

class MouseButtonEvent: public Event
{
private:
    uint16_t keycode;

public:
    explicit MouseButtonEvent(uint16_t keycode, void *raw = nullptr, VNsize rawSize = 0):
        Event(raw, rawSize),
        keycode(keycode)
    {}
    [[nodiscard]]
    uint16_t getKeyCode() const noexcept { return this->keycode; }
};

class MouseButtonPressedEvent: public MouseButtonEvent
{
public:
    explicit MouseButtonPressedEvent(uint16_t keycode, void *raw = nullptr, VNsize rawSize = 0):
        MouseButtonEvent(keycode, raw, rawSize)
        {}

    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::MouseButtonPressed; }
    [[nodiscard]]
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
    explicit MouseButtonReleasedEvent(uint16_t keycode, void *raw = nullptr, VNsize rawSize = 0):
    MouseButtonEvent(keycode, raw, rawSize)
    {}

    [[nodiscard]]
    Event::Type getType() const noexcept override { return Event::Type::MouseButtonReleased; }
    [[nodiscard]]
    std::string toString() const noexcept override
    {
        std::stringstream ss;

        ss << "MouseButtonReleased: " << (uint16_t)this->getKeyCode();
        return ss.str();
    }
};

}

#endif //VANADIUM_MOUSEEVENT_H
