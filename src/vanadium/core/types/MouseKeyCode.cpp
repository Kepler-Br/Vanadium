#include "MouseKeyCode.h"

#include "vanadium/core/Assert.h"
#include "vanadium/core/StringHash.h"

namespace vanadium::mouse {

std::string toString(KeyCode arg) {
  switch (arg) {
    case KeyCode::Unknown:
      return "Unknown";
    case KeyCode::Left:
      return "Left";
    case KeyCode::Middle:
      return "Middle";
    case KeyCode::Right:
      return "Right";
    case KeyCode::X1:
      return "X1";
    case KeyCode::X2:
      return "X2";
    default:
      VAN_DEBUGBREAK;
      VAN_ENGINE_ASSERT(false, "Unknown mouse::KeyCode!");
      return "Unknown";
  }
}

KeyCode fromString(const std::string &arg) {
  size_t hash = hashString(arg);

  switch (hash) {
    case "Left"_hash:
      return KeyCode::Left;
    case "Middle"_hash:
      return KeyCode::Middle;
    case "Right"_hash:
      return KeyCode::Right;
    case "X1"_hash:
      return KeyCode::X1;
    case "X2"_hash:
      return KeyCode::X2;
    default:
      VAN_DEBUGBREAK;
      VAN_ENGINE_ASSERT(false, "Unknown mouse KeyCode string!");
      return KeyCode::Unknown;
  }
}

KeyCode fromInt(int arg) {
  switch (arg) {
    case (int)KeyCode::Left:
      return KeyCode::Left;
    case (int)KeyCode::Middle:
      return KeyCode::Middle;
    case (int)KeyCode::Right:
      return KeyCode::Right;
    case (int)KeyCode::X1:
      return KeyCode::X1;
    case (int)KeyCode::X2:
      return KeyCode::X2;
    default:
      VAN_DEBUGBREAK;
      VAN_ENGINE_ASSERT(false, "Unknown mouse KeyCode scancode!");
      return KeyCode::Unknown;
  }
}

}  // namespace vanadium::mouse
