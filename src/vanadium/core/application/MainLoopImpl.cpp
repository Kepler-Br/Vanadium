#include "MainLoopImpl.h"

#include <fmt/format.h>

#include <utility>

#include "vanadium/core/Assert.h"
#include "vanadium/core/interfaces/Application.h"
#include "vanadium/core/interfaces/FactoryContainer.h"
#include "vanadium/core/interfaces/State.h"
#include "vanadium/core/interfaces/constructed/EventProvider.h"
#include "vanadium/core/interfaces/constructed/StateStack.h"
#include "vanadium/core/interfaces/constructed/factories/LoggerFactory.h"
#include "vanadium/core/interfaces/constructed/factories/StopwatchFactory.h"

namespace vanadium {

MainLoopImpl::MainLoopImpl(Ref<EngineEndStateStack> stateStack,
                           Ref<EngineEndEventProvider> eventProvider,
                           Ref<FactoryContainer> factoryContainer)
    : _stateStack(std::move(stateStack)),
      _eventProvider(std::move(eventProvider)),
      _factoryContainer(std::move(factoryContainer)) {
  VAN_ENGINE_ASSERT((this->_stateStack != nullptr), "stateStack is nullptr!");
  VAN_ENGINE_ASSERT((this->_eventProvider != nullptr),
                    "eventProvider is nullptr!");
  VAN_ENGINE_ASSERT((this->_factoryContainer != nullptr),
                    "factoryContainer is nullptr!");

  this->_frameTime = this->_factoryContainer->construct<StopwatchFactory>();
  this->_logger = this->_factoryContainer->construct<LoggerFactory>("MainLoopImpl");

  this->_logger->trace("Initialized");
}

MainLoopImpl::~MainLoopImpl() { this->_logger->trace("Destroyed"); }

#pragma region EngineEndMainLoop

void MainLoopImpl::tick() {
  this->_deltaTime = this->_frameTime->restart();

  if (this->_timeSinceLastFixedUpdate > this->_fixedTimeThreshold ||
      this->_deltaTime > this->_deltaTimeThreshold) {
    this->_logger->warn(
        fmt::format("MainLoopImpl::tick: overslept!\n"
                    "Time since last fixed update: {}; Threshold: {}\n"
                    "DeltaTime: {}; Threshold: {}",
                    this->_timeSinceLastFixedUpdate, this->_fixedTimeThreshold,
                    this->_deltaTime, this->_deltaTimeThreshold));

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

#pragma endregion

}  // namespace vanadium
