#pragma once

#include <string>

namespace vanadium::mouse {

enum class KeyCode {
  Unknown = 0,
  Left = 1,
  Middle = 2,
  Right = 3,
  X1 = 4,  // What are these?
  X2 = 5,  //
};

std::string toString(KeyCode arg);
KeyCode fromString(const std::string &arg);
KeyCode fromInt(int arg);

}  // namespace vanadium::mouse
