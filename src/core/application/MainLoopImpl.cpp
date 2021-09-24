#include "MainLoopImpl.h"

#include <fmt/format.h>

#include <utility>

#include "core/Log.h"
#include "core/Stopwatch.h"
#include "core/interfaces/Application.h"
#include "core/interfaces/EventProvider.h"
#include "core/interfaces/State.h"
#include "core/interfaces/StateStack.h"

namespace vanadium {

MainLoopImpl::MainLoopImpl(Ref<EngineEndApplication> application,
                           Ref<EngineEndStateStack> stateStack,
                           Ref<EngineEndEventProvider> eventProvider)
    : _frameTime(Stopwatch::create(false)),
      _stateStack(std::move(stateStack)),
      _application(std::move(application)),
      _eventProvider(std::move(eventProvider)) {}

#pragma region EngineEndMainLoop

void MainLoopImpl::tick() {
  this->_deltaTime = this->_frameTime->restart();

  if (this->_timeSinceLastFixedUpdate > this->_fixedTimeThreshold ||
      this->_deltaTime > this->_deltaTimeThreshold) {
    VAN_ENGINE_WARN(
        "MainLoopImpl::tick: overslept!\n"
        "Time since last fixed update: {}; Threshold: {}\n"
        "DeltaTime: {}; Threshold: {}",
        this->_timeSinceLastFixedUpdate, this->_fixedTimeThreshold,
        this->_deltaTime, this->_deltaTimeThreshold);

    if (this->_timeSinceLastFixedUpdate > this->_fixedTimeThreshold) {
      this->_timeSinceLastFixedUpdate = this->_fixedTimeThreshold;
    }

    if (this->_deltaTime > this->_deltaTimeThreshold) {
      this->_deltaTime = this->_deltaTimeThreshold;
    }
  }

  Ref<State> topState = this->_stateStack->top();

  this->_eventProvider->update();
  this->_eventProvider->dispatch();
  topState->onTickStart();
  topState->update(this->_deltaTime);

  while (this->_timeSinceLastFixedUpdate > this->_fixedUpdateTime) {
    topState->fixedUpdate(this->_fixedUpdateTime);
    this->_timeSinceLastFixedUpdate -= this->_fixedUpdateTime;
    this->_fixedUpdateTicks++;
  }

  topState->preRender();
  topState->render();
  topState->postRender();
  topState->onTickEnd();

  this->_stateStack->executeCommands();
  this->_ticksSinceStart++;
  this->_secondsSinceStart += this->_deltaTime;
  this->_timeSinceLastFixedUpdate += this->_deltaTime;
}

void MainLoopImpl::run() {
  while (!this->_stateStack->empty()) {
    this->tick();
  }
}

#pragma endregion

#pragma region MainLoop

void MainLoopImpl::setFixedUpdateTime(float fixedUpdateTime) noexcept {
  this->_fixedUpdateTime = fixedUpdateTime;
  this->_fixedTimeThreshold =
      this->_fixedUpdateTime * this->_thresholdFixedUpdateSteps;
}

float MainLoopImpl::getDeltaTime() const noexcept { return this->_deltaTime; }

float MainLoopImpl::getFixedUpdateTime() const noexcept {
  return this->_fixedUpdateTime;
}

double MainLoopImpl::getSecondsSinceStart() const noexcept {
  return this->_secondsSinceStart;
}

std::size_t MainLoopImpl::getTicksSinceStart() const noexcept {
  return this->_ticksSinceStart;
}

std::size_t MainLoopImpl::getFixedUpdateTicks() const noexcept {
  return this->_fixedUpdateTicks;
}

Ref<Application> MainLoopImpl::getApplication() { return this->_application; }

Ref<StateStack> MainLoopImpl::getStateStack() { return this->_stateStack; }

Ref<EventProvider> MainLoopImpl::getEventProvider() {
  return this->_eventProvider;
}

#pragma endregion

}  // namespace vanadium
