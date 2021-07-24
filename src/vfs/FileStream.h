#ifndef VANADIUM_FILESTREAM_H
#define VANADIUM_FILESTREAM_H

#include <physfs.h>

#include <glm/gtc/type_ptr.hpp>

#include "../core/Types.h"

namespace vanadium::vfs {

enum class OpenMode {
  Append = 0,
  Input,
  Output,
};

class FileStream {
 protected:
  PHYSFS_File *_handle = nullptr;
  bool _errorOccurred = false;
  bool _isFileOpen = false;

 public:
  explicit FileStream(const std::string &path, OpenMode mode = OpenMode::Input);
  FileStream() = default;
  FileStream(const FileStream &) = delete;
  void operator=(const FileStream &) = delete;
  ~FileStream();

  bool open(const std::string &path, OpenMode mode);
  [[nodiscard]] bool fail() const;
  bool seek(std::streamsize pos) noexcept;
  std::streamsize tell() noexcept;
  std::streamsize write(const void *buffer, std::streamsize length);
  std::streamsize read(void *buffer, std::streamsize length);
  std::streamsize length();
  bool eof() noexcept;
  bool flush();
  bool close();
  void resetErrorFlag();

  bool operator!() const noexcept;
  FileStream &operator<<(const bool &arg);
  FileStream &operator<<(const short &arg);
  FileStream &operator<<(const unsigned short &arg);
  FileStream &operator<<(const int &arg);
  FileStream &operator<<(const unsigned int &arg);
  FileStream &operator<<(const long int &arg);
  FileStream &operator<<(const unsigned long int &arg);
  FileStream &operator<<(const long long int &arg);
  FileStream &operator<<(const unsigned long long int &arg);
  FileStream &operator<<(const char &arg);
  FileStream &operator<<(const unsigned char &arg);
  FileStream &operator<<(const std::string &arg);
  FileStream &operator<<(const float &arg);
  FileStream &operator<<(const double &arg);
  FileStream &operator<<(const glm::vec2 &arg);
  FileStream &operator<<(const glm::vec3 &arg);
  FileStream &operator<<(const glm::vec4 &arg);
  FileStream &operator<<(const glm::ivec2 &arg);
  FileStream &operator<<(const glm::ivec3 &arg);
  FileStream &operator<<(const glm::ivec4 &arg);
  FileStream &operator<<(const glm::mat4 &arg);
  FileStream &operator<<(const glm::mat3 &arg);
  FileStream &operator<<(const glm::mat2 &arg);

  FileStream &operator>>(bool &arg);
  FileStream &operator>>(short &arg);
  FileStream &operator>>(unsigned short &arg);
  FileStream &operator>>(int &arg);
  FileStream &operator>>(unsigned int &arg);
  FileStream &operator>>(long int &arg);
  FileStream &operator>>(unsigned long int &arg);
  FileStream &operator>>(long long int &arg);
  FileStream &operator>>(unsigned long long int &arg);
  FileStream &operator>>(char &arg);
  FileStream &operator>>(unsigned char &arg);
  FileStream &operator>>(float &arg);
  FileStream &operator>>(double &arg);
  FileStream &operator>>(glm::vec2 &arg);
  FileStream &operator>>(glm::vec3 &arg);
  FileStream &operator>>(glm::vec4 &arg);
  FileStream &operator>>(glm::ivec2 &arg);
  FileStream &operator>>(glm::ivec3 &arg);
  FileStream &operator>>(glm::ivec4 &arg);
  FileStream &operator>>(glm::mat4 &arg);
  FileStream &operator>>(glm::mat3 &arg);
  FileStream &operator>>(glm::mat2 &arg);
};

}  // namespace vanadium::vfs
#endif  // VANADIUM_FILESTREAM_H
