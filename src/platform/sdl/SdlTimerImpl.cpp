#include "SdlTimerImpl.h"

#include "SdlIncludes.h"

namespace vanadium {

SdlTimerImpl::SdlTimerImpl(std::function<void(float)> callback, float seconds,
                           bool repeating)
    : _callback(std::move(callback)), _repeating(repeating), _target(seconds) {}

void SdlTimerImpl::start() {
  this->_isRunning = true;
  this->_current = 0.0f;
  this->_sdlStartTicks = SDL_GetTicks();
}

float SdlTimerImpl::stop() {
  float current = this->_current;
  this->_isRunning = false;
  this->_current = 0.0f;

  return current;
}

float SdlTimerImpl::update() {
  if (!this->_isRunning) {
    return this->_current;
  }

  uint32_t now = SDL_GetTicks();

  float current = (float)(now - this->_sdlStartTicks)/1000.0f;

  if (current >= this->_target) {
    if (this->_callback != nullptr) {
      this->_callback(current);
    }

    this->_current = 0.0f;

    if (!this->_repeating) {
      this->_isRunning = false;
    } else {
      this->_sdlStartTicks = now;
    }
  } else {
    this->_current = current;
  }

  return current;
}

bool SdlTimerImpl::isRunning() noexcept {
  return this->_isRunning;
}

float SdlTimerImpl::getCurrentTime() noexcept { return this->_current; }

void SdlTimerImpl::setRepeating(bool repeating) noexcept {
  this->_repeating = repeating;
}

bool SdlTimerImpl::getRepeating() noexcept { return this->_repeating; }

void SdlTimerImpl::setCallback(
    const std::function<void(float)>& callback) noexcept {
  this->_callback = callback;
}

void SdlTimerImpl::setTime(float seconds) noexcept {
  this->_target = seconds;
  this->_current = 0.0f;
}

float SdlTimerImpl::getTime() noexcept {
  return this->_target;
}

}  // namespace vanadium
