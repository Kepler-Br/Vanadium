#include "vfs/Vfs.h"

#include "core/Log.h"
#include "vfs/InputFileStream.h"

namespace vanadium::vfs {

bool init(const std::string &workingDirectory) {
  int returnStatus;

  if (PHYSFS_isInit() != 0) {
    return true;
  }
  if (workingDirectory.empty()) {
    returnStatus = PHYSFS_init(nullptr);
  } else {
    returnStatus = PHYSFS_init(workingDirectory.c_str());
  }
  if (returnStatus == 0) {
    return false;
  }

  return true;
}
// PhysFS and Vanadium VFS errors are interchangeable.
ErrorCode getErrorCode() { return (ErrorCode)PHYSFS_getLastErrorCode(); }

std::string errorCodeToString(ErrorCode code) {
  return PHYSFS_getErrorByCode((PHYSFS_ErrorCode)code);
}

std::string getError() {
  PHYSFS_ErrorCode errorCode = PHYSFS_getLastErrorCode();
  const char *errorMessage = PHYSFS_getErrorByCode(errorCode);

  return errorMessage;
}

void discardErrors() { PHYSFS_getLastErrorCode(); }

std::vector<char> readWhole(const std::string &path) {
  std::vector<char> data;
  InputFileStream file(path);
  auto fileSize = file.getLength();

  if (!file || fileSize < 0) {
    return data;
  }

  data.resize(fileSize);
  file.read(data.data(), fileSize);

  if (!file) {
    return {};
  }

  return data;
}

std::string readAsString(const std::string &path) {
  std::string source;
  InputFileStream file(path);
  std::streamsize fileSize = file.getLength();

  if (!file || fileSize < 0) {
    return source;
  }

  source.resize(fileSize);
  file.read(source.data(), fileSize);

  if (!file) {
    return {};
  }

  return source;
}

bool isInit() { return PHYSFS_isInit() != 0; }

bool deinit() { return PHYSFS_deinit() != 0; }

bool mount(const std::string &physicalPath, const std::string &mountPoint,
           int appendToPath) {
  bool result =
      PHYSFS_mount(physicalPath.c_str(), mountPoint.c_str(), appendToPath) != 0;

  return result;
}

bool unmount(const std::string &physicalPath) {
  bool result = PHYSFS_unmount(physicalPath.c_str()) != 0;

  return result;
}

bool isDirectory(const std::string &path) {
  PHYSFS_Stat stat;

  if (PHYSFS_stat(path.c_str(), &stat) == 0) {
    return false;
  }
  if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY) {
    return true;
  }
  return false;
}

bool isRegularFile(const std::string &path) {
  PHYSFS_Stat stat;

  if (PHYSFS_stat(path.c_str(), &stat) == 0) {
    return false;
  }
  if (stat.filetype == PHYSFS_FILETYPE_REGULAR) {
    return true;
  }

  return false;
}

bool isReadonly(const std::string &path) {
  PHYSFS_Stat stat;

  if (PHYSFS_stat(path.c_str(), &stat) == 0) {
    return false;
  }
  return stat.readonly != 0;
}

size_t fileSize(const std::string &path) {
  PHYSFS_Stat stat;

  if (PHYSFS_stat(path.c_str(), &stat) == 0) {
    return 0;
  }

  return stat.filesize;
}

bool exists(const std::string &path) {
  return PHYSFS_exists(path.c_str()) != 0;
}

bool createDirectories(const std::string &path) {
  return PHYSFS_mkdir(path.c_str()) != 0;
}

bool deleteFile(const std::string &path) {
  return PHYSFS_delete(path.c_str()) != 0;
}

std::vector<std::string> listDirectory(const std::string &path) {
  std::vector<std::string> fileList;
  char **rc = PHYSFS_enumerateFiles(path.c_str());
  std::size_t totalDirs = 0;

  for (char **i = rc; *i != nullptr; i++) {
    totalDirs++;
  }

  fileList.reserve(totalDirs);

  for (char **i = rc; *i != nullptr; i++) {
    fileList.emplace_back(*i);
  }

  PHYSFS_freeList(rc);

  return fileList;
}

std::vector<std::string> listSearchPath() {
  std::vector<std::string> searchPathList;
  char **searchPathRawList = PHYSFS_getSearchPath();
  std::size_t searchPathListSize = 0;

  for (char **i = searchPathRawList; *i != nullptr; i++) {
    searchPathListSize++;
  }

  searchPathList.reserve(searchPathListSize);

  for (char **i = searchPathRawList; *i != nullptr; i++) {
    searchPathList.emplace_back(*i);
  }

  PHYSFS_freeList(searchPathRawList);

  return searchPathList;
}

}  // namespace vanadium::vfs