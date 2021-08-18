#pragma once

#include <physfs.h>

#include <istream>
#include <memory>

#include "FileStreamBuffer.h"

namespace vanadium::vfs {

class InputFileStream : public std::istream {
 private:
  PHYSFS_File* _fileHandle = nullptr;
  std::unique_ptr<FileStreamBuffer> _fileStreamBuffer;
  std::string _path;

 public:
  InputFileStream();
  explicit InputFileStream(const std::string& path);
  ~InputFileStream() override;

  void close();
  void open(const std::string& path);
  bool isOpen() const;
  std::streamsize getLength();
  std::string getPath() const;
};

}  // namespace vanadium::vfs
