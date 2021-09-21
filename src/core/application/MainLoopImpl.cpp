#include "MainLoopImpl.h"

#include <utility>

#include "core/Dialogs.h"
#include "core/EventProvider.h"
#include "core/Exceptions.h"
#include "core/Stopwatch.h"
#include "core/application/ApplicationImpl.h"
#include "core/application/StateStack.h"

namespace vanadium {

MainLoopImpl::MainLoopImpl(Ref<Application> application,
                           Ref<StateStack> stateStack,
                           Ref<EventProvider> eventProvider)
    : _frameTime(Stopwatch::create(false)),
      _application(std::move(application)),
      _stateStack(std::move(stateStack)),
      _eventProvider(std::move(eventProvider)) {}

void MainLoopImpl::deinitialize() {
  this->_application = nullptr;
  this->_stateStack = nullptr;
  this->_eventProvider = nullptr;
}

void MainLoopImpl::tick() {
  State *topState;

  this->_deltatime = this->_frameTime->stop();
  this->_frameTime->start();
  topState = this->_stateStack->top();
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
    try {
      this->tick();
    } catch (const ExecutionInterrupted &e) {
      std::string message =
          fmt::format("Execution interrupted with message: {}", e.what());
      VAN_ENGINE_CRITICAL(message);
      if (e.showDialog()) {
        bool result =
            Dialogs::show("Application error", message, DialogType::Error);
        if (!result) {
          VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
        }
      }
      this->_stateStack->popAll();
    }
  }
}

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

}  // namespace vanadium
