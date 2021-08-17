#pragma once

#include <physfs.h>

#include <iostream>
#include <istream>
#include <streambuf>
#include <vector>

namespace vanadium::vfs {

class FileStreamBuffer : public std::streambuf {
 private:
  std::vector<char_type> _buffer;
  PHYSFS_File* _fileHandle;
  bool _isFailure = false;

  void setFailFlag(bool flag);

 public:
  explicit FileStreamBuffer(PHYSFS_File* fileHandle,
                            std::size_t bufferSize = 2048);

  ~FileStreamBuffer() override = default;

  bool operator!() const;

  void resetFailFlag();

 protected:
  int_type underflow() override;

  int_type overflow(int_type c) override;

  pos_type seekoff(off_type pos, std::ios_base::seekdir dir,
                   std::ios_base::openmode mode) override;

  pos_type seekpos(pos_type pos, std::ios_base::openmode mode) override;

  int sync() override;
};

}  // namespace vanadium::vfs
