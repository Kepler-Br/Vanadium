#include "VfsSubsystem.h"

#include <utility>

#include "core/Exceptions.h"
#include "core/Log.h"
#include "vfs/Vfs.h"

namespace vanadium {

VfsSubsystem::VfsSubsystem(std::string workingDirectory)
    : Subsystem("VFS"), _workingDirectory(std::move(workingDirectory)) {}

void VfsSubsystem::init() {
  VAN_ENGINE_TRACE("Initializing VFS subsystem.");

  if (!vfs::init(this->_workingDirectory)) {
    const std::string &errorMessage =
        fmt::format("VFS initialization failed: {}.", vfs::getError());

    VAN_ENGINE_CRITICAL(errorMessage);
    throw SubsystemInitializationException(errorMessage);
  }
}

void VfsSubsystem::shutdown() {
  VAN_ENGINE_TRACE("Shutting down VFS subsystem.");

  if (!vfs::deinit()) {
    VAN_ENGINE_CRITICAL("VFS shutting down failed: {}.", vfs::getError());
  }
}

}  // namespace vanadium
