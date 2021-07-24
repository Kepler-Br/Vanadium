#include "DefaultStopwatch.h"

#include "DefaultIncludes.h"

namespace vanadium {

void DefaultStopwatch::start() noexcept {
  this->isRunning = true;
  this->time = SDL_GetTicks();
}

double DefaultStopwatch::stop() noexcept {
  if (this->isRunning) {
    this->isRunning = false;
    return (double)(SDL_GetTicks() - this->time) / 1000.0;
  } else
    return 0.0;
}

}  // namespace vanadium
