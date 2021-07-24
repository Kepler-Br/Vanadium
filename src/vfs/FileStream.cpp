#include "vfs/FileStream.h"

#include <string>

namespace vanadium {

namespace vfs {

FileStream::FileStream(const std::string &path, OpenMode mode) {
  this->open(path, mode);
}

FileStream::~FileStream() {
  this->flush();
  this->close();
}

bool FileStream::open(const std::string &path, OpenMode mode) {
  if (this->_handle != nullptr) {
    return false;
  }
  if (mode == OpenMode::Append)
    this->_handle = PHYSFS_openAppend(path.c_str());
  else if (mode == OpenMode::Output)
    this->_handle = PHYSFS_openWrite(path.c_str());
  else if (mode == OpenMode::Input)
    this->_handle = PHYSFS_openRead(path.c_str());
  else {
    this->_isFileOpen = false;
    return false;
  }
  this->_errorOccurred = this->_handle == nullptr;
  if (this->_errorOccurred) {
    this->_isFileOpen = false;
  }
  this->_isFileOpen = true;
  return this->_errorOccurred;
}

bool FileStream::fail() const { return this->_errorOccurred; }

bool FileStream::seek(std::streamsize pos) noexcept {
  int resultStatus = PHYSFS_seek(this->_handle, pos);

  if (resultStatus == 0) {
    this->_errorOccurred = true;
  }
  return resultStatus != 0;
}

std::streamsize FileStream::tell() noexcept {
  if (this->_errorOccurred) {
    return -1;
  }
  std::streamsize position = PHYSFS_tell(this->_handle);

  if (position == -1) {
    this->_errorOccurred = true;
  }
  return position;
}

std::streamsize FileStream::write(const void *buffer, std::streamsize length) {
  if (this->_errorOccurred) {
    return -1;
  }
  std::streampos wrote = PHYSFS_writeBytes(this->_handle, buffer, length);

  if (wrote != length) {
    this->_errorOccurred = true;
  }
  return wrote;
}

std::streamsize FileStream::read(void *buffer, std::streamsize length) {
  if (this->_errorOccurred) {
    return -1;
  }
  std::streamsize red = PHYSFS_readBytes(this->_handle, buffer, length);

  if (red == -1) {
    this->_errorOccurred = true;
  }
  return red;
}

std::streamsize FileStream::length() {
  if (this->_errorOccurred) {
    return -1;
  }
  std::streamsize result = PHYSFS_fileLength(this->_handle);

  if (result == -1) {
    this->_errorOccurred = true;
  }
  return result;
}

bool FileStream::eof() noexcept {
  if (this->_errorOccurred) {
    return true;
  }
  return PHYSFS_eof(this->_handle) != 0;
}

bool FileStream::flush() {
  if (this->_errorOccurred) {
    return false;
  }
  if (!this->_isFileOpen) {
    this->_errorOccurred = true;
    return false;
  }
  int returnStatus = PHYSFS_flush(this->_handle);

  if (returnStatus == 0) {
    this->_errorOccurred = true;
    return false;
  }
  return true;
}

bool FileStream::close() {
  if (!this->_isFileOpen) {
    return false;
  }
  int returnStatus = PHYSFS_close(this->_handle);

  if (returnStatus == 0) {
    this->_errorOccurred = true;
    return false;
  }
  this->_handle = nullptr;
  this->_errorOccurred = false;
  this->_isFileOpen = false;
  return true;
}

void FileStream::resetErrorFlag() { this->_errorOccurred = false; }

bool FileStream::operator!() const noexcept { return _errorOccurred; }

FileStream &FileStream::operator<<(const bool &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const short &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const unsigned short &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const int &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const unsigned int &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const long &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const unsigned long &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const long long int &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const unsigned long long int &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const char &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const unsigned char &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const std::string &arg) {
  this->write((void *)arg.c_str(), arg.size() * sizeof(char));
  return *this;
}

FileStream &FileStream::operator<<(const float &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const double &arg) {
  this->write((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator<<(const glm::ivec2 &arg) {
  this->write((void *)glm::value_ptr(arg), sizeof(arg.x) * 2);
  return *this;
}

FileStream &FileStream::operator<<(const glm::ivec3 &arg) {
  this->write((void *)glm::value_ptr(arg), sizeof(arg.x) * 3);
  return *this;
}

FileStream &FileStream::operator<<(const glm::ivec4 &arg) {
  this->write((void *)glm::value_ptr(arg), sizeof(arg.x) * 4);
  return *this;
}

FileStream &FileStream::operator<<(const glm::mat4 &arg) {
  this->write((void *)glm::value_ptr(arg),
              sizeof(*glm::value_ptr(arg)) * 4 * 4);
  return *this;
}

FileStream &FileStream::operator<<(const glm::mat3 &arg) {
  this->write((void *)glm::value_ptr(arg),
              sizeof(*glm::value_ptr(arg)) * 3 * 3);
  return *this;
}

FileStream &FileStream::operator<<(const glm::mat2 &arg) {
  this->write((void *)glm::value_ptr(arg),
              sizeof(*glm::value_ptr(arg)) * 2 * 2);
  return *this;
}

FileStream &FileStream::operator<<(const glm::vec4 &arg) {
  this->write((void *)glm::value_ptr(arg), sizeof(arg.x) * 4);
  return *this;
}

FileStream &FileStream::operator<<(const glm::vec3 &arg) {
  this->write((void *)glm::value_ptr(arg), sizeof(arg.x) * 3);
  return *this;
}

FileStream &FileStream::operator<<(const glm::vec2 &arg) {
  this->write((void *)glm::value_ptr(arg), sizeof(arg.x) * 2);
  return *this;
}

/*
 * Write operations.
 */

FileStream &FileStream::operator>>(bool &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(short &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(unsigned short &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(int &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(unsigned int &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(long &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(unsigned long &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(long long int &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(unsigned long long int &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(char &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(unsigned char &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(float &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(double &arg) {
  this->read((void *)&arg, sizeof(arg));
  return *this;
}

FileStream &FileStream::operator>>(glm::ivec2 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg.x) * 2);
  return *this;
}

FileStream &FileStream::operator>>(glm::ivec3 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg.x) * 3);
  return *this;
}

FileStream &FileStream::operator>>(glm::ivec4 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg.x) * 4);
  return *this;
}

FileStream &FileStream::operator>>(glm::mat4 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg[0]) * 4 * 4);
  return *this;
}

FileStream &FileStream::operator>>(glm::mat3 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg[0]) * 3 * 3);
  return *this;
}

FileStream &FileStream::operator>>(glm::mat2 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg[0]) * 2 * 2);
  return *this;
}

FileStream &FileStream::operator>>(glm::vec4 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg.x) * 4);
  return *this;
}

FileStream &FileStream::operator>>(glm::vec3 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg.x) * 3);
  return *this;
}

FileStream &FileStream::operator>>(glm::vec2 &arg) {
  this->read((void *)glm::value_ptr(arg), sizeof(arg.x) * 2);
  return *this;
}
}  // namespace vfs

}  // namespace vanadium