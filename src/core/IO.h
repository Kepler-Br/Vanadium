#ifndef VANADIUM_IO_H
#define VANADIUM_IO_H

#include <glm/vec2.hpp>
#include <sstream>
#include <tuple>
#include <vector>

#include "Types.h"
namespace Vanadium {

class IO {
 private:
  static IO *instance;

 public:
  virtual bool fail() noexcept = 0;
  virtual std::string readAsString(const std::string &path) noexcept = 0;
  virtual std::vector<char> read(const std::string &path) noexcept = 0;
  virtual void write(const std::string &path, void *data, VNsize dataSize,
                     bool overwrite) noexcept = 0;
  virtual std::vector<std::string> listDirectory(
      const std::string &path) noexcept = 0;
  virtual void removeAll(const std::string &path) noexcept = 0;
  virtual void remove(const std::string &path) noexcept = 0;
  virtual void createFile(const std::string &path) noexcept = 0;
  virtual void makeDir(const std::string &path) noexcept = 0;
  virtual void makeDirs(const std::string &path) noexcept = 0;
  virtual VNsize fileSize(const std::string &path) noexcept = 0;
  virtual bool fileExists(const std::string &path) noexcept = 0;
  virtual bool isRegularFile(const std::string &path) noexcept = 0;
  virtual bool isDirectory(const std::string &path) noexcept = 0;

  static IO *getInstance();
};

}  // namespace Vanadium

#endif  // VANADIUM_IO_H
