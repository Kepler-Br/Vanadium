#pragma once

#include <glm/vec2.hpp>

#include "Event.h"

namespace vanadium {

class WindowResizedEvent : public Event {
 private:
  uint _newWidth;
  uint _newHeight;

 public:
  WindowResizedEvent(uint newWidth, uint newHeight, void *raw = nullptr,
                     size_t rawSize = 0)
      : Event(raw, rawSize), _newWidth(newWidth), _newHeight(newHeight) {}

  [[nodiscard]] uint getWidth() const noexcept { return this->_newWidth; }

  [[nodiscard]] uint getHeight() const noexcept { return this->_newHeight; }

  [[nodiscard]] glm::ivec2 getNewGeometry() const noexcept {
    return {this->_newWidth, this->_newHeight};
  }

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::WindowResized;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("WindowSizeChangedEvent: ({}, {})", this->_newWidth,
                       this->_newHeight);
  }
};

class WindowCloseEvent : public Event {
 public:
  WindowCloseEvent(void *raw = nullptr, size_t rawSize = 0)
      : Event(raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::WindowClose;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return "WindowCloseEvent";
  }
};

class WindowFocusLostEvent : public Event {
 public:
  WindowFocusLostEvent(void *raw = nullptr, size_t rawSize = 0)
      : Event(raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::WindowLostFocus;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return "WindowFocusLostEvent";
  }
};

class WindowFocusGainEvent : public Event {
 public:
  WindowFocusGainEvent(void *raw = nullptr, size_t rawSize = 0)
      : Event(raw, rawSize) {}

  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::WindowGainFocus;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return "WindowFocusGainEvent";
  }
};

}  // namespace vanadium
