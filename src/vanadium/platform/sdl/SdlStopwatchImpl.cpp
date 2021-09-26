#include "SdlStopwatchImpl.h"

#include "vanadium/platform/sdl/SdlIncludes.h"

namespace vanadium {

void SdlStopwatchImpl::start() noexcept {
  this->_isRunning = true;
  this->_time = SDL_GetTicks();
}

float SdlStopwatchImpl::stop() noexcept {
  if (this->_isRunning) {
    this->_isRunning = false;
    return (float)(SDL_GetTicks() - this->_time) / 1000.0f;
  } else {
    return 0.0f;
  }
}

float SdlStopwatchImpl::restart() noexcept {
  float time = this->stop();
  this->start();

  return time;
}

}  // namespace vanadium
