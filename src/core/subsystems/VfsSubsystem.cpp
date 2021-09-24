#include "VfsSubsystem.h"

#include <utility>

#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/interfaces/Application.h"
#include "core/types/application/ApplicationProperties.h"
#include "vfs/Vfs.h"

namespace vanadium {

VfsSubsystem::VfsSubsystem() : _name("vfs"), _initializationStage(1) {}

VfsSubsystem::VfsSubsystem(std::string name, std::size_t initializationStage)
    : _name(std::move(name)), _initializationStage(initializationStage) {}

void VfsSubsystem::initialize(EngineEndApplication *application) {
  VAN_ENGINE_TRACE("Initializing {} subsystem.", this->_name);

  const auto &props = application->getProperties();
  const auto &args = props.getArguments();

  if (args.empty()) {
    const std::string &errorMessage =
        "VFS initialization failed: program args empty. "
        "Need first argument to be program root directory.";

    VAN_ENGINE_CRITICAL(errorMessage);
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
  VAN_ENGINE_TRACE("Deinitializing {} subsystem.", this->_name);

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
