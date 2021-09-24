#include "SdlSubsystem.h"

#include "core/Exceptions.h"
#include "core/Log.h"
#include "platform/sdl/SdlIncludes.h"

namespace vanadium {

SdlSubsystem::SdlSubsystem() : _name("sdl"), _initializationStage(1) {}

SdlSubsystem::SdlSubsystem(std::string name, std::size_t initializationStage)
    : _name(std::move(name)), _initializationStage(initializationStage) {}

void SdlSubsystem::initialize(EngineEndApplication *application) {
  VAN_ENGINE_TRACE("Initializing {} subsystem.", this->_name);

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    const std::string errorMessage =
        fmt::format("Cannot initialize SDL2 subsystems: {}", SDL_GetError());

    throw SubsystemInitializationException(errorMessage);
  }
}

void SdlSubsystem::deinitialize() {
  VAN_ENGINE_TRACE("Deinitializing {} subsystem.", this->_name);

  SDL_Quit();
}

const std::string &SdlSubsystem::getName() const noexcept {
  return this->_name;
}

std::size_t SdlSubsystem::getInitializationStage() const noexcept {
  return this->_initializationStage;
}

bool SdlSubsystem::isInitialized() const noexcept { return this->_initialized; }

}  // namespace vanadium
