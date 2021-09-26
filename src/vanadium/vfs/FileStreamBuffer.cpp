#include "FileStreamBuffer.h"

namespace vanadium::vfs {

void FileStreamBuffer::setFailFlag(bool flag) {
  if (this->_isFailure) {
    return;
  }
  this->_isFailure = flag;
}

FileStreamBuffer::FileStreamBuffer(PHYSFS_File* fileHandle,
                                   std::size_t bufferSize)
    : _fileHandle(fileHandle) {
  this->_buffer.resize(bufferSize);

  char_type* start = this->_buffer.data();
  char_type* end = start + bufferSize;

  this->setg(start, end, end);
  this->setp(start, end);
}

void FileStreamBuffer::resetFailFlag() { this->_isFailure = false; }

bool FileStreamBuffer::operator!() const { return this->_isFailure; }

std::streambuf::int_type FileStreamBuffer::underflow() {
  if (PHYSFS_eof(this->_fileHandle)) {
    return traits_type::eof();
  }

  if (this->gptr() < this->egptr()) {
    return traits_type::to_int_type(*this->gptr());
  }

  std::size_t bytesRead =
      PHYSFS_readBytes(this->_fileHandle, this->_buffer.data(),
                       this->_buffer.size() * sizeof(char_type));

  if (bytesRead < 1) {
    this->setFailFlag(bytesRead == -1);

    return traits_type::eof();
  }

  char_type* bufferStart = this->_buffer.data();

  this->setg(bufferStart, bufferStart, bufferStart + bytesRead);

  return traits_type::to_int_type(*this->gptr());
}

std::streambuf::int_type FileStreamBuffer::overflow(
    std::streambuf::int_type c) {
  if (this->pptr() == this->pbase() && c == traits_type::eof()) {
    return traits_type::not_eof(c);  // no-op
  }

  PHYSFS_uint64 len = this->pptr() - this->pbase();
  PHYSFS_sint64 bytesWrote =
      PHYSFS_writeBytes(this->_fileHandle, this->pbase(), len);

  if (bytesWrote < 1) {
    this->setFailFlag(bytesWrote == -1);

    return traits_type::eof();
  }

  if (c != traits_type::eof()) {
    bytesWrote = PHYSFS_writeBytes(this->_fileHandle, &c, sizeof(char_type));

    this->setFailFlag(bytesWrote == -1);

    if (bytesWrote < 1) {
      return traits_type::eof();
    }
  }

  return traits_type::not_eof(c);
}

std::streambuf::pos_type FileStreamBuffer::seekoff(
    std::streambuf::off_type pos, std::ios_base::seekdir dir,
    std::ios_base::openmode mode) {
  if (dir == std::ios_base::beg) {
    this->setFailFlag(PHYSFS_seek(this->_fileHandle, pos) == 0);
  } else if (dir == std::ios_base::cur) {
    PHYSFS_uint64 newPos =
        (PHYSFS_tell(this->_fileHandle) + pos) - (this->egptr() - this->gptr());

    this->setFailFlag(PHYSFS_seek(this->_fileHandle, newPos) == 0);
  } else if (dir == std::ios_base::end) {
    PHYSFS_uint64 newPos = PHYSFS_fileLength(this->_fileHandle) + pos;

    this->setFailFlag(PHYSFS_seek(this->_fileHandle, newPos) == 0);
  }

  if (mode & std::ios_base::in) {
    this->setg(this->egptr(), this->egptr(), this->egptr());
  }
  if (mode & std::ios_base::out) {
    this->setp(this->_buffer.data(), this->_buffer.data());
  }

  if (this->_isFailure) {
    return off_type(-1);
  }

  return PHYSFS_tell(this->_fileHandle);
}

std::streambuf::pos_type FileStreamBuffer::seekpos(
    std::streambuf::pos_type pos, std::ios_base::openmode mode) {
  this->setFailFlag(PHYSFS_seek(this->_fileHandle, pos) == 0);

  if (mode & std::ios_base::in) {
    this->setg(this->egptr(), this->egptr(), this->egptr());
  }
  if (mode & std::ios_base::out) {
    this->setp(this->_buffer.data(), this->_buffer.data());
  }

  if (this->_isFailure) {
    return off_type(-1);
  }

  return PHYSFS_tell(this->_fileHandle);
}

int FileStreamBuffer::sync() { return this->overflow(traits_type::eof()); }

}  // namespace vanadium::vfs
