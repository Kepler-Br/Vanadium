#include "DefaultStopwatch.h"

#include "platform/sdl/SdlIncludes.h"

namespace vanadium {

void DefaultStopwatch::start() noexcept {
  this->_isRunning = true;
  this->_time = SDL_GetTicks();
}

float DefaultStopwatch::stop() noexcept {
  if (this->_isRunning) {
    this->_isRunning = false;
    return (float)(SDL_GetTicks() - this->_time) / 1000.0f;
  } else
    return 0.0f;
}

float DefaultStopwatch::restart() noexcept {
  float time = this->stop();
  this->start();

  return time;
}

}  // namespace vanadium
