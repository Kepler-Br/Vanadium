#include "DefaultStopwatch.h"

#include "platform/sdl/SdlIncludes.h"

namespace vanadium {

void DefaultStopwatch::start() noexcept {
  this->_isRunning = true;
  this->_time = SDL_GetTicks();
}

double DefaultStopwatch::stop() noexcept {
  if (this->_isRunning) {
    this->_isRunning = false;
    return (double)(SDL_GetTicks() - this->_time) / 1000.0;
  } else
    return 0.0;
}

}  // namespace vanadium
