#include "AppInitHook.h"

#include <fmt/format.h>
#include <vanadium/core/Exceptions.h>
#include <vanadium/vfs/Vfs.h>

AppInitHook::AppInitHook(vanadium::Ref<vanadium::LoggerFactory> loggerFactory) {
  this->_logger = loggerFactory->construct("AppInitHook");
}

void AppInitHook::afterSubsystemInit(
    vanadium::EngineEndApplication *application,
    const vanadium::Ref<vanadium::Subsystem> &subsystem) {
  if (subsystem->getName() == "vfs") {
    using namespace vanadium;

    const std::string mountPath = "resources";

    if (!vfs::mount(mountPath, "resources")) {
      std::string message =
          fmt::format("Failed to mount virtual file system at path '{}': {}.",
                      mountPath, vfs::getError());

      throw InitializationInterrupted(message);
    }

    this->_logger->trace("Mounted VFS to {}", mountPath);
  }
}
