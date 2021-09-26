#include "VfsSubsystem.h"

#include <utility>

#include "vanadium/core/Exceptions.h"
#include "vanadium/core/Log.h"
#include "vanadium/core/interfaces/Application.h"
#include "vanadium/vfs/Vfs.h"

namespace vanadium {

VfsSubsystem::VfsSubsystem() : _name("vfs"), _initializationStage(1) {}

VfsSubsystem::VfsSubsystem(std::string name, std::size_t initializationStage)
    : _name(std::move(name)), _initializationStage(initializationStage) {}

void VfsSubsystem::initialize(EngineEndApplication *application) {
  const auto &props = application->getProperties();
  const auto &args = props.getArguments();

  if (args.empty()) {
    const std::string &errorMessage =
        "VFS initialization failed: program args empty. "
        "Need first argument to be program root directory.";

    throw SubsystemInitializationException(errorMessage);
  }

  const std::string &workingDirectory = args[0];

  if (!vfs::init(workingDirectory)) {
    const std::string &errorMessage =
        fmt::format("VFS initialization failed: {}.", vfs::getError());

    throw SubsystemInitializationException(errorMessage);
  }
}

void VfsSubsystem::deinitialize() {
  if (!vfs::deinit()) {
    VAN_ENGINE_ERROR("VFS shutting down failed: {}.", vfs::getError());
  }
}

const std::string &VfsSubsystem::getName() const noexcept {
  return this->_name;
}

std::size_t VfsSubsystem::getInitializationStage() const noexcept {
  return this->_initializationStage;
}

bool VfsSubsystem::isInitialized() const noexcept { return this->_initialized; }

}  // namespace vanadium
