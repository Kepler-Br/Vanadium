#include "EntryPoint.h"

void EntryPoint::setupVfs() {
  using namespace vanadium;

  const std::string mountPath = "resources";
  if (!vfs::mount(mountPath, "resources")) {
    std::string message =
        fmt::format("Failed to mount virtual file system at path '{}': {}.",
                    mountPath, vfs::getError());
    VAN_USER_CRITICAL(message);
    throw InitializationInterrupted(message);
  }
}

void EntryPoint::preInit() { this->setupVfs(); }

void EntryPoint::postInit() {}
