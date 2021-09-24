#pragma once

#include <glm/vec2.hpp>

#include "Event.h"
#include "core/MouseKeyCode.h"

namespace vanadium {

class MouseMoveEvent : public Event {
 private:
  int32_t _newXPosition;
  int32_t _newYPosition;
  int32_t _deltaX;
  int32_t _deltaY;

 public:
  MouseMoveEvent(int32_t newXPosition, int32_t newYPosition, int32_t deltaX,
                 int32_t deltaY, void *raw = nullptr, size_t rawSize = 0)
      : Event(raw, rawSize),
        _newXPosition(newXPosition),
        _newYPosition(newYPosition),
        _deltaX(deltaX),
        _deltaY(deltaY) {}

  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format(
        "MouseMoveEvent. New position: ({}, {}); Delta: ({}, {});",
        this->_newXPosition, this->_newYPosition, this->_deltaX, this->_deltaY);
  }

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseMove;
  }

  [[nodiscard]] int32_t getNewXPosition() const noexcept {
    return this->_newXPosition;
  }

  [[nodiscard]] int32_t getNewYPosition() const noexcept {
    return this->_newYPosition;
  }

  [[nodiscard]] int32_t getDeltaX() const noexcept { return this->_deltaX; }

  [[nodiscard]] int32_t getDeltaY() const noexcept { return this->_deltaY; }

  [[nodiscard]] glm::ivec2 getNewPosition() const noexcept {
    return {this->_newXPosition, this->_newYPosition};
  }

  [[nodiscard]] glm::ivec2 getDelta() const noexcept {
    return {this->_deltaX, this->_deltaY};
  }
};

class MouseScrollEvent : public Event {
 private:
  int _verticalScroll = 0;
  int _horizontalScroll = 0;

 public:
  MouseScrollEvent(int vertical, int horizontal, void *raw = nullptr,
                   size_t rawSize = 0)
      : Event(raw, rawSize),
        _verticalScroll(vertical),
        _horizontalScroll(horizontal) {}

  [[nodiscard]] int getVerticalScroll() const noexcept {
    return this->_verticalScroll;
  }

  [[nodiscard]] int getHorizontalScroll() const noexcept {
    return this->_horizontalScroll;
  }

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseScroll;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("MouseScrollEvent. Vertical: {}; Horizontal: {}.",
                       this->_verticalScroll, this->_horizontalScroll);
  };
};

class MouseButtonEvent : public Event {
 private:
  mouse::KeyCode _keycode;

 public:
  explicit MouseButtonEvent(mouse::KeyCode keycode, void *raw = nullptr,
                            size_t rawSize = 0)
      : Event(raw, rawSize), _keycode(keycode) {}

  [[nodiscard]] mouse::KeyCode getKeyCode() const noexcept {
    return this->_keycode;
  }
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  using MouseButtonEvent::MouseButtonEvent;

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseButtonPressed;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("MouseButtonPressedEvent: {} ({})", this->getKeyCode(),
                       mouse::toString(this->getKeyCode()));
  }
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  using MouseButtonEvent::MouseButtonEvent;

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::MouseButtonReleased;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("MouseButtonReleased: {} ({})", this->getKeyCode(),
                       mouse::toString(this->getKeyCode()));
  }
};

}  // namespace vanadium
