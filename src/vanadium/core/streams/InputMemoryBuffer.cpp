#include "InputMemoryBuffer.h"

namespace vanadium {

InputMemoryBuffer::InputMemoryBuffer(char *pointer, size_t size) : _size(size) {
  this->setg(pointer, pointer, pointer + this->_size);
}

std::streambuf::pos_type InputMemoryBuffer::seekoff(off_type pos,
                                               std::ios_base::seekdir dir,
                                               std::ios_base::openmode mode) {
  if (dir == std::ios_base::beg) {
    if (pos < 0 || (size_t)pos >= this->_size) {
      return off_type(-1);
    }

    char *newCurrentPosition = this->eback() + pos;

    this->setg(this->eback(), newCurrentPosition, this->egptr());

    return pos;
  } else if (dir == std::ios_base::cur) {
    const off_type currentPosition =
        (off_type)this->gptr() - (off_type)this->eback();

    if ((currentPosition + pos) < 0 || (currentPosition + pos) >= this->_size) {
      return off_type(-1);
    }

    this->setg(this->eback(), this->gptr() + pos, this->egptr());

    return currentPosition + pos;
  } else if (dir == std::ios_base::end) {
    const auto size = (off_type)this->_size;

    if (size - 1 + pos >= size || size - 1 + pos < 0) {
      return off_type(-1);
    }

    this->setg(this->eback(), this->egptr() + pos, this->egptr());

    return size - 1 + pos;
  }

  return off_type(-1);
}

}  // namespace vanadium
