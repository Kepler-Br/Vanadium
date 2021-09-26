#pragma once

#include <physfs.h>

#include <memory>
#include <ostream>

#include "FileStreamBuffer.h"

namespace vanadium::vfs {

class OutputFileStream : public std::ostream {
 private:
  PHYSFS_File* _fileHandle = nullptr;
  std::unique_ptr<FileStreamBuffer> _fileStreamBuffer;
  std::string _path;

 public:
  OutputFileStream() = default;
  explicit OutputFileStream(const std::string& path,
                            std::ios_base::openmode mode = std::ios_base::ate);
  ~OutputFileStream() override;

  void close();
  void open(const std::string& path,
            std::ios_base::openmode mode = std::ios_base::ate);
  bool isOpen() const;
  std::streamsize getLength();
  std::string getPath() const;
};

}  // namespace vanadium::vfs