#include "OutputFileStream.h"

namespace vanadium::vfs {

OutputFileStream::OutputFileStream() : basic_ostream(nullptr) {}

OutputFileStream::OutputFileStream(const std::string& path,
                                   std::ios_base::openmode mode)
    : basic_ostream(nullptr) {
  this->open(path, mode);
}

OutputFileStream::~OutputFileStream() { this->close(); }

void OutputFileStream::close() {
  if (!this->isOpen()) {
    this->setstate(std::ios_base::failbit);

    return;
  }

  this->flush();
  PHYSFS_flush(this->_fileHandle);

  int ret = PHYSFS_close(this->_fileHandle);

  if (ret != 0) {
    this->clear();
    this->_fileHandle = nullptr;
    this->_path = "";
  } else {
    this->setstate(std::ios_base::failbit);
  }
}

void OutputFileStream::open(const std::string& path,
                            std::ios_base::openmode mode) {
  if (this->isOpen()) {
    this->setstate(std::ios_base::failbit);
    return;
  }

  PHYSFS_ErrorCode errorCode = PHYSFS_getLastErrorCode();

  if (mode & std::ios_base::ate) {
    this->_fileHandle = PHYSFS_openAppend(path.c_str());
  } else if (mode & std::ios_base::out) {
    this->_fileHandle = PHYSFS_openWrite(path.c_str());
  } else {
    this->setstate(std::ios_base::failbit);
    return;
  }

  // File already created by PhysFS, so, no need to say that it's not found.
  if (errorCode == PHYSFS_ErrorCode::PHYSFS_ERR_OK &&
      PHYSFS_getLastErrorCode() == PHYSFS_ErrorCode::PHYSFS_ERR_NOT_FOUND) {
    PHYSFS_setErrorCode(PHYSFS_ErrorCode::PHYSFS_ERR_OK);
  }

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

bool OutputFileStream::isOpen() const {
  return this->_fileHandle != nullptr && PHYSFS_isInit();
}

std::streamsize OutputFileStream::getLength() {
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

const std::string &OutputFileStream::getPath() const { return this->_path; }

}  // namespace vanadium::vfs