#include "AppInitHook.h"

#include <core/Exceptions.h>
#include <fmt/format.h>

#include "vfs/Vfs.h"

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
  }
}
