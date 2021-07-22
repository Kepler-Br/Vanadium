#ifndef VANADIUM_MOUSEEVENT_H
#define VANADIUM_MOUSEEVENT_H

#include <glm/vec2.hpp>

#include "../core/KeyCodes.h"
#include "Event.h"

namespace vanadium {

class MouseMoveEvent : public Event {
 private:
  int32_t newXPosition;
  int32_t newYPosition;
  int32_t deltaX;
  int32_t deltaY;

 public:
  MouseMoveEvent(int32_t newXPosition, int32_t newYPosition, int32_t deltaX,
                 int32_t deltaY, void *raw = nullptr, size_t rawSize = 0)
      : Event(raw, rawSize),
        newXPosition(newXPosition),
        newYPosition(newYPosition),
        deltaX(deltaX),
        deltaY(deltaY) {}
  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format(
        "MouseMoveEvent. New position: ({}, {}); Delta: ({}, {});",
        this->newXPosition, this->newYPosition, this->deltaX, this->deltaY);
  }
  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseMove;
  }
  [[nodiscard]] int32_t getNewXPosition() const noexcept {
    return this->newXPosition;
  }
  [[nodiscard]] int32_t getNewYPosition() const noexcept {
    return this->newYPosition;
  }
  [[nodiscard]] int32_t getDeltaX() const noexcept { return this->deltaX; }
  [[nodiscard]] int32_t getDeltaY() const noexcept { return this->deltaY; }
  [[nodiscard]] glm::ivec2 getNewPosition() const noexcept {
    return {this->newXPosition, this->newYPosition};
  }
  [[nodiscard]] glm::ivec2 getDelta() const noexcept {
    return {this->deltaX, this->deltaY};
  }
};

class MouseScrollEvent : public Event {
 private:
  int verticalScroll = 0;
  int horizontalScroll = 0;

 public:
  MouseScrollEvent(int vertical, int horizontal, void *raw = nullptr,
                   size_t rawSize = 0)
      : Event(raw, rawSize),
        verticalScroll(vertical),
        horizontalScroll(horizontal) {}
  [[nodiscard]] int getVerticalScroll() const noexcept {
    return this->verticalScroll;
  }
  [[nodiscard]] int getHorizontalScroll() const noexcept {
    return this->horizontalScroll;
  }
  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseScroll;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("MouseScrollEvent. Vertical: {}; Horizontal: {}.",
                       this->verticalScroll, this->horizontalScroll);
  };
};

class MouseButtonEvent : public Event {
 private:
  uint16_t keycode;

 public:
  explicit MouseButtonEvent(uint16_t keycode, void *raw = nullptr,
                            size_t rawSize = 0)
      : Event(raw, rawSize), keycode(keycode) {}
  [[nodiscard]] uint16_t getKeyCode() const noexcept { return this->keycode; }
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonPressedEvent(uint16_t keycode, void *raw = nullptr,
                                   size_t rawSize = 0)
      : MouseButtonEvent(keycode, raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseButtonPressed;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("MouseButtonPressedEvent: {}", this->getKeyCode());
  }
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonReleasedEvent(uint16_t keycode, void *raw = nullptr,
                                    size_t rawSize = 0)
      : MouseButtonEvent(keycode, raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseButtonReleased;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("MouseButtonReleased: {}", this->getKeyCode());
  }
};

}  // namespace Vanadium

#endif  // VANADIUM_MOUSEEVENT_H
