#include "platform/default/DefaultIO.h"

#include <filesystem>

namespace vanadium {

bool DefaultIO::fail() noexcept { return this->_isFail; }

std::vector<char> DefaultIO::read(const std::string &path) noexcept {
  std::ifstream file(path, std::ios::binary);
  std::vector<char> data;

  if (!file) {
    this->_isFail = true;
    return data;
  }

  file.seekg(0, std::ios_base::end);
  size_t size = (size_t)file.tellg();
  data.resize(size);
  file.seekg(0, std::ios_base::beg);
  file.read(&data[0], (std::streamsize)size);
  if (!file)
    this->_isFail = true;
  else
    this->_isFail = false;
  return data;
}

std::string DefaultIO::readAsString(const std::string &path) noexcept {
  std::stringstream ss;
  std::ifstream file(path, std::ios::binary);

  if (!file) {
    this->_isFail = true;
    return std::string();
  }
  ss << file.rdbuf();
  if (!file)
    this->_isFail = true;
  else
    this->_isFail = false;
  return ss.str();
}

void DefaultIO::write(const std::string &path, void *data, size_t dataSize,
                      bool overwrite) noexcept {
  std::ofstream file;

  if (overwrite)
    file = std::ofstream(path, std::ios::binary | std::ios::trunc);
  else
    file = std::ofstream(path, std::ios::binary | std::ios_base::app);
  if (!file) {
    this->_isFail = true;
    return;
  }
  file.write((char *)data, (long)dataSize);
  if (!file)
    this->_isFail = true;
  else
    this->_isFail = false;
}

std::vector<std::string> DefaultIO::listDirectory(
    const std::string &path) noexcept {
  std::vector<std::string> dirList;
  std::error_code err;

  for (const auto &entry : std::filesystem::directory_iterator(path, err)) {
    dirList.emplace_back(entry.path().string());
  }
  this->_isFail = (bool)err;
  return dirList;
}

void DefaultIO::removeAll(const std::string &path) noexcept {
  std::error_code err;

  std::filesystem::remove_all(path, err);
  this->_isFail = (bool)err;
}

void DefaultIO::remove(const std::string &path) noexcept {
  std::error_code err;

  std::filesystem::remove(path, err);
  this->_isFail = (bool)err;
}

void DefaultIO::createFile(const std::string &path) noexcept {
  std::ofstream file(path);

  if (!file) {
    this->_isFail = true;
  } else {
    this->_isFail = false;
  }
}

void DefaultIO::makeDir(const std::string &path) noexcept {
  std::error_code err;

  std::filesystem::create_directory(path, err);
  this->_isFail = (bool)err;
}

void DefaultIO::makeDirs(const std::string &path) noexcept {
  std::error_code err;

  std::filesystem::create_directories(path, err);
  this->_isFail = (bool)err;
}

size_t DefaultIO::fileSize(const std::string &path) noexcept {
  std::error_code err;
  size_t size = std::filesystem::file_size(path, err);

  this->_isFail = (bool)err;
  return size;
}

bool DefaultIO::fileExists(const std::string &path) noexcept {
  std::error_code err;
  bool result = std::filesystem::exists(path, err);

  this->_isFail = (bool)err;
  return result;
}

bool DefaultIO::isRegularFile(const std::string &path) noexcept {
  std::error_code err;
  bool result = std::filesystem::is_regular_file(path, err);

  this->_isFail = (bool)err;
  return result;
}

bool DefaultIO::isDirectory(const std::string &path) noexcept {
  std::error_code err;
  bool result = std::filesystem::is_directory(path, err);

  this->_isFail = (bool)err;
  return result;
}

}  // namespace vanadium