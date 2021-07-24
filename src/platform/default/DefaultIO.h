#ifndef VANADIUM_PLATFORM_DEFAULTIO_H
#define VANADIUM_PLATFORM_DEFAULTIO_H

#include <fstream>

#include "core/IO.h"

namespace vanadium {

class DefaultIO : public IO {
 protected:
  bool _isFail = false;

 public:
  bool fail() noexcept override;
  std::vector<char> read(const std::string &path) noexcept override;
  std::string readAsString(const std::string &path) noexcept override;
  void write(const std::string &path, void *data, size_t dataSize,
             bool overwrite) noexcept override;
  std::vector<std::string> listDirectory(
      const std::string &path) noexcept override;
  void removeAll(const std::string &path) noexcept override;
  void remove(const std::string &path) noexcept override;
  void createFile(const std::string &path) noexcept override;
  void makeDir(const std::string &path) noexcept override;
  void makeDirs(const std::string &path) noexcept override;
  size_t fileSize(const std::string &path) noexcept override;
  bool fileExists(const std::string &path) noexcept override;
  bool isRegularFile(const std::string &path) noexcept override;
  bool isDirectory(const std::string &path) noexcept override;
};

}  // namespace vanadium

#endif  // VANADIUM_PLATFORM_DEFAULTIO_H
