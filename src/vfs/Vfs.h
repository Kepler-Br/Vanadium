#ifndef VANADIUM_VFS_H
#define VANADIUM_VFS_H

#include <physfs.h>

#include <cstring>
#include <string>
#include <vector>

namespace vanadium::vfs {

// See PhysFS errors.
enum class ErrorCode {
  OK = PHYSFS_ERR_OK,
  OtherError = PHYSFS_ERR_OTHER_ERROR,
  OutOfMemory = PHYSFS_ERR_OUT_OF_MEMORY,
  NotInitialized = PHYSFS_ERR_NOT_INITIALIZED,
  IsInitialized = PHYSFS_ERR_IS_INITIALIZED,
  Argv0IsNull = PHYSFS_ERR_ARGV0_IS_NULL,
  Unsupported = PHYSFS_ERR_UNSUPPORTED,
  PastEof = PHYSFS_ERR_PAST_EOF,
  FilesStillOpen = PHYSFS_ERR_FILES_STILL_OPEN,
  InvalidArgument = PHYSFS_ERR_INVALID_ARGUMENT,
  NotMounted = PHYSFS_ERR_NOT_MOUNTED,
  NotFound = PHYSFS_ERR_NOT_FOUND,
  SymlinkForbidden = PHYSFS_ERR_SYMLINK_FORBIDDEN,
  NoWriteDir = PHYSFS_ERR_NO_WRITE_DIR,
  OpenForReading = PHYSFS_ERR_OPEN_FOR_READING,
  OpenForWriting = PHYSFS_ERR_OPEN_FOR_WRITING,
  NotAFile = PHYSFS_ERR_NOT_A_FILE,
  ReadOnly = PHYSFS_ERR_READ_ONLY,
  Corrupt = PHYSFS_ERR_CORRUPT,
  SymlinkLoop = PHYSFS_ERR_SYMLINK_LOOP,
  IO = PHYSFS_ERR_IO,
  Permission = PHYSFS_ERR_PERMISSION,
  NoSpace = PHYSFS_ERR_NO_SPACE,
  BadFilename = PHYSFS_ERR_BAD_FILENAME,
  Busy = PHYSFS_ERR_BUSY,
  DirNotEmpty = PHYSFS_ERR_DIR_NOT_EMPTY,
  OSError = PHYSFS_ERR_OS_ERROR,
  Duplicate = PHYSFS_ERR_DUPLICATE,
  BadPassword = PHYSFS_ERR_BAD_PASSWORD,
  AppCallback = PHYSFS_ERR_APP_CALLBACK,
};

bool init(const std::string &workingDirectory);
bool isInit();
bool deinit();
ErrorCode getErrorCode();
std::string errorCodeToString(ErrorCode code);
std::string getError();
void discardErrors();
std::vector<char> readWhole(const std::string &path);
std::string readAsString(const std::string &path);
bool mount(const std::string &physicalPath, const std::string &mountPoint,
           int appendToPath = 1);
bool unmount(const std::string &physicalPath);
bool isDirectory(const std::string &path);
bool isRegularFile(const std::string &path);
bool isReadonly(const std::string &path);
size_t fileSize(const std::string &path);
bool exists(const std::string &path);
bool createDirectories(const std::string &path);
bool deleteFile(const std::string &path);
std::vector<std::string> listDirectory(const std::string &path = "");
// What?
std::vector<std::string> listSearchPath();

}  // namespace vanadium::vfs

#endif  // VANADIUM_VFS_H
