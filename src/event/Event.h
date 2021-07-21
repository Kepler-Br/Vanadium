#ifndef VANADIUM_EVENT_H
#define VANADIUM_EVENT_H

#include <string>

#include "core/Assert.h"
#include "core/Types.h"

namespace Vanadium {

// enum EventCategory
//{
//     EventCategoryNone           = 0,
//     EventCategoryKey            = 1 << 0,
//     EventCategoryMouse          = 1 << 1,
//     EventCategoryMouseButton    = 1 << 2,
//     EventCategoryWindow         = 1 << 3,
// };

class Event {
 public:
  enum class Type {
    Any = 0,
    KeyPressed,
    KeyReleased,
    MouseMove,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseScroll,
    WindowSizeChanged,
    WindowClose,
    WindowLostFocus,
    WindowGainFocus,
  };

 private:
  bool handled = false;
  char *raw;

 public:
  explicit Event(void *raw = nullptr, size_t rawSize = 0) {
    if (raw != nullptr && rawSize != 0) {
      this->raw = new char[rawSize];
      memcpy(this->raw, raw, rawSize);
    }
  }
  virtual ~Event() { delete[] raw; }
  [[nodiscard]] virtual Event::Type getType() const noexcept = 0;
  [[nodiscard]] virtual std::string toString() const noexcept = 0;
  [[nodiscard]] bool isHandled() const noexcept { return this->handled; }
  void setAsHandled() noexcept { this->handled = true; }
  virtual void *getRaw() noexcept { return (void *)this->raw; }

  static std::string typeToString(Event::Type type) noexcept {
    switch (type) {
      case Event::Type::KeyPressed:
        return "KeyPressed";
      case Event::Type::KeyReleased:
        return "KeyReleased";
      case Event::Type::MouseMove:
        return "MouseMove";
      case Event::Type::MouseButtonPressed:
        return "MouseButtonPressed";
      case Event::Type::MouseButtonReleased:
        return "MouseButtonReleased";
      case Event::Type::MouseScroll:
        return "MouseScroll";
      case Event::Type::WindowSizeChanged:
        return "WindowSizeChanged";
      case Event::Type::WindowClose:
        return "WindowClose";
      case Event::Type::Any:
        return "Any";
      case Event::Type::WindowLostFocus:
        return "WindowLostFocus";
      case Event::Type::WindowGainFocus:
        return "WindowGainFocus";
    }
    VAN_ENGINE_ASSERT(false, "Unknown event type!");
    return std::string("");
  }
};

}  // namespace Vanadium

#endif  // VANADIUM_EVENT_H
