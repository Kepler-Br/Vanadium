#include "MainLoopImpl.h"

#include <SDL_error.h>
#include <fmt/format.h>

#include <utility>

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/Stopwatch.h"
#include "core/application/State.h"
#include "core/interfaces/Application.h"
#include "core/interfaces/EventProvider.h"
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
  this->_deltatime = this->_frameTime->stop();
  this->_frameTime->start();
  Ref<State> topState = this->_stateStack->top();
  this->_eventProvider->dispatch();
  this->_eventProvider->update();
  topState->onTickStart();
  topState->update(this->_deltatime);
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
  this->_secondsSinceStart += this->_deltatime;
  this->_timeSinceLastFixedUpdate += this->_deltatime;
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
}

float MainLoopImpl::getDeltatime() const noexcept { return this->_deltatime; }

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
