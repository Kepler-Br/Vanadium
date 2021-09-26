#pragma once

#include <istream>

#include "InputMemoryBuffer.h"

namespace vanadium {

class InputMemoryStream : public std::istream {
 private:
  InputMemoryBuffer _buffer;

 public:
  InputMemoryStream(char *p, size_t l);
};

}  // namespace vanadium
