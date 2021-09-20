#include "InputMemoryStream.h"

namespace vanadium {

InputMemoryStream::InputMemoryStream(char *p, size_t l)
    : std::istream(&_buffer), _buffer(p, l) {
  rdbuf(&_buffer);
}

}  // namespace vanadium
