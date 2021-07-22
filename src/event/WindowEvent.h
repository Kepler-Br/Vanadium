#ifndef VANADIUM_WINDOWEVENT_H
#define VANADIUM_WINDOWEVENT_H

#include <glm/vec2.hpp>

#include "../core/Types.h"
#include "Event.h"

namespace vanadium {

class WindowSizeChangedEvent : public Event {
 private:
  uint newWidth;
  uint newHeight;

 public:
  WindowSizeChangedEvent(uint newWidth, uint newHeight, void *raw = nullptr,
                         size_t rawSize = 0)
      : Event(raw, rawSize), newWidth(newWidth), newHeight(newHeight) {}

  [[nodiscard]] uint getWidth() const noexcept { return this->newWidth; }
  [[nodiscard]] uint getHeight() const noexcept { return this->newHeight; }
  [[nodiscard]] glm::ivec2 getNewGeometry() const noexcept {
    return {this->newWidth, this->newHeight};
  }
  [[nodiscard]] Event::Type getType() const noexcept override {
    return Event::Type::WindowSizeChanged;
  }
  [[nodiscard]] std::string toString() const noexcept override {
    return fmt::format("WindowSizeChangedEvent: ({}, {})", this->newWidth,
                       this->newHeight);
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

}  // namespace Vanadium
#endif  // VANADIUM_WINDOWEVENT_H
