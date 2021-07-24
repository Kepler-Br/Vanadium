#include "vfs/Entry.h"

#include <physfs.h>

#include <utility>

#include "vfs/Exceptions.h"

namespace vanadium::vfs {

Entry::Entry(std::string workingDirectory)
    : workingDirectory(std::move(workingDirectory)) {
  int returnStatus;
  if (PHYSFS_isInit()) return;
  if (this->workingDirectory.empty())
    returnStatus = PHYSFS_init(nullptr);
  else
    returnStatus = PHYSFS_init(workingDirectory.c_str());
  if (returnStatus == 0) {
    PHYSFS_ErrorCode errorCode = PHYSFS_getLastErrorCode();
    const char *errorMessage = PHYSFS_getErrorByCode(errorCode);
    throw VfsError(errorMessage);
  }
}

Entry::~Entry() { PHYSFS_deinit(); }

}  // namespace vanadium::vfs