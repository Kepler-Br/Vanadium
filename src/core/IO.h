#pragma once

#include <vector>

#include "Types.h"

namespace vanadium {

class IO {
 public:
  virtual ~IO() = default;

  virtual bool fail() noexcept = 0;
  virtual std::string readAsString(const std::string &path) noexcept = 0;
  virtual std::vector<char> read(const std::string &path) noexcept = 0;
  virtual void write(const std::string &path, std::byte *data, size_t dataSize,
                     bool overwrite) noexcept = 0;
  virtual std::vector<std::string> listDirectory(
      const std::string &path) noexcept = 0;
  virtual void removeAll(const std::string &path) noexcept = 0;
  virtual void remove(const std::string &path) noexcept = 0;
  virtual void createFile(const std::string &path) noexcept = 0;
  virtual void makeDir(const std::string &path) noexcept = 0;
  virtual void makeDirs(const std::string &path) noexcept = 0;
  virtual size_t fileSize(const std::string &path) noexcept = 0;
  virtual bool fileExists(const std::string &path) noexcept = 0;
  virtual bool isRegularFile(const std::string &path) noexcept = 0;
  virtual bool isDirectory(const std::string &path) noexcept = 0;

  static Ref<IO> create();
};

}  // namespace vanadium
