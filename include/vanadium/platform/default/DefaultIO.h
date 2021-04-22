#ifndef VANADIUM_DEFAULTIO_H
#define VANADIUM_DEFAULTIO_H

#include <fstream>

#include "core/IO.h"

namespace Vanadium {

class DefaultIO : public IO {
 private:
  bool isFail = false;

 public:
  bool fail() noexcept override;
  std::vector<char> read(const std::string &path) noexcept override;
  std::string readAsString(const std::string &path) noexcept override;
  void write(const std::string &path, void *data, VNsize dataSize,
             bool overwrite) noexcept override;
  std::vector<std::string> listDirectory(
      const std::string &path) noexcept override;
  void removeAll(const std::string &path) noexcept override;
  void remove(const std::string &path) noexcept override;
  void createFile(const std::string &path) noexcept override;
  void makeDir(const std::string &path) noexcept override;
  void makeDirs(const std::string &path) noexcept override;
  VNsize fileSize(const std::string &path) noexcept override;
  bool fileExists(const std::string &path) noexcept override;
  bool isRegularFile(const std::string &path) noexcept override;
  bool isDirectory(const std::string &path) noexcept override;
};

}  // namespace Vanadium

#endif  // VANADIUM_DEFAULTIO_H
