#include "InputFileStream.h"

namespace vanadium::vfs {

InputFileStream::InputFileStream() : std::istream(nullptr) {}

InputFileStream::InputFileStream(const std::string& path)
    : std::istream(nullptr) {
  this->open(path);
}

InputFileStream::~InputFileStream() { this->close(); }

void InputFileStream::close() {
  if (!this->isOpen() || !PHYSFS_isInit()) {
    this->setstate(std::ios_base::failbit);

    return;
  }

  int ret = PHYSFS_close(this->_fileHandle);

  if (ret != 0) {
    this->clear();
    this->_fileHandle = nullptr;
    this->_path = "";
  } else {
    this->setstate(std::ios_base::failbit);
  }
}

void InputFileStream::open(const std::string& path) {
  if (this->isOpen()) {
    this->setstate(std::ios_base::failbit);
    return;
  }

  this->_fileHandle = PHYSFS_openRead(path.c_str());

  if (this->_fileHandle == nullptr) {
    this->setstate(std::ios_base::failbit);
    return;
  }

  this->_path = path;
  this->_fileStreamBuffer =
      std::make_unique<FileStreamBuffer>(this->_fileHandle);
  this->rdbuf(this->_fileStreamBuffer.get());
  this->clear();
}

bool InputFileStream::isOpen() const {
  return this->_fileHandle != nullptr && PHYSFS_isInit();
}

std::streamsize InputFileStream::getLength() {
  if (!this->isOpen()) {
    return 0;
  }

  PHYSFS_sint64 ret = PHYSFS_fileLength(this->_fileHandle);

  if (ret == -1) {
    this->setstate(std::ios_base::failbit);
    return 0;
  }

  return ret;
}

std::string InputFileStream::getPath() const { return this->_path; }

}  // namespace vanadium::vfs
