#include "SdlSubsystem.h"

#include "core/Exceptions.h"
#include "core/Log.h"
#include "platform/sdl/SdlIncludes.h"

namespace vanadium {

SdlSubsystem::SdlSubsystem() : Subsystem("SDL") {}

void SdlSubsystem::init() {
  VAN_ENGINE_TRACE("Initializing SDL2 subsystem.");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    const std::string errorMessage =
        fmt::format("Cannot initialize SDL2 subsystems: {}", SDL_GetError());

    VAN_ENGINE_CRITICAL(errorMessage);
    throw SubsystemInitializationException(errorMessage);
  }
}

void SdlSubsystem::shutdown() {
  VAN_ENGINE_TRACE("Shutting down SDL2 subsystem.");
  SDL_Quit();
}

}  // namespace vanadium
