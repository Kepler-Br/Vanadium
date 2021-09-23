#include "ApplicationImpl.h"

#include <utility>

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/interfaces/EventProvider.h"
#include "core/interfaces/MainLoop.h"
#include "core/interfaces/StateStack.h"
#include "core/interfaces/Subsystem.h"

namespace vanadium {

#pragma region private

void ApplicationImpl::initializeSubsystemByStage(std::size_t stage) {
  for (auto &subsystem : this->_subsystems) {
    if (subsystem->getInitializationStage() == stage) {
      subsystem->initialize(*this);
    }
  }
}

#pragma endregion

ApplicationImpl::ApplicationImpl(Ref<EngineEndMainLoop> mainLoop,
                                 Ref<EngineEndStateStack> stateStack,
                                 Ref<EngineEndEventProvider> eventProvider)
    : _eventProvider(std::move(eventProvider)),
      _stateStack(std::move(stateStack)),
      _mainLoop(std::move(mainLoop)) {}

ApplicationImpl::~ApplicationImpl() {
  VAN_ENGINE_INFO("Destroying Application.");

  std::for_each(this->_subsystems.rbegin(), this->_subsystems.rend(),
                [](const auto &subsystem) { subsystem->shutdown(); });
}

#pragma region Application

Ref<EventProvider> ApplicationImpl::getEventProvider() noexcept {
  return this->_eventProvider;
}

Ref<Window> ApplicationImpl::getWindow() noexcept { return this->_window; }

Ref<StateStack> ApplicationImpl::getStateStack() noexcept {
  return this->_stateStack;
}

Ref<MainLoop> ApplicationImpl::getMainLoop() noexcept {
  return this->_mainLoop;
}

void ApplicationImpl::stop() { this->_stateStack->requestPopAll(); }

const ApplicationProperties &ApplicationImpl::getProperties() const noexcept {
  return this->_properties;
}

#pragma endregion

#pragma region EngineEndApplication

void ApplicationImpl::run() {
  if (this->_initializationInterrupted) {
    VAN_ENGINE_INFO(
        "Initialization was interrupted. ApplicationImpl::run execution "
        "stopped.");
    return;
  }

  try {
    this->_mainLoop->run();
  } catch (const ExecutionInterrupted &e) {
    std::string message =
        fmt::format("Execution interrupted with message: {}", e.what());
    VAN_ENGINE_CRITICAL(message);
    if (e.showDialog()) {
      Dialogs::show("Application error", message, DialogType::Error);
    }
    this->_stateStack->popAll();
  }
}

void ApplicationImpl::setProperties(const ApplicationProperties &properties) {
  this->_properties = properties;

  try {
    constexpr std::size_t subsystemStages = 3;

    std::vector<std::size_t> subsystemsPerStage;
    subsystemsPerStage.resize(subsystemStages, 0);

    for (const auto &subsystem : this->_subsystems) {
      std::size_t subsystemStage = subsystem->getInitializationStage();

      if (subsystemStage >= subsystemsPerStage.size()) {
        subsystemsPerStage.back()++;
      } else {
        subsystemsPerStage[subsystemStage]++;
      }
      subsystem->initialize(*this);
    }

    if (subsystemsPerStage[0] != 0) {
      this->initializeSubsystemByStage(0);
    }

    if (subsystemsPerStage[1] != 0) {
      this->initializeSubsystemByStage(1);
    }

    this->_window = Window::create(this->_properties.getWindowProperties());

    if (subsystemsPerStage[2] != 0) {
      this->initializeSubsystemByStage(2);
    }
  } catch (const InitializationInterrupted &e) {
    const std::string message = fmt::format(
        "Initialization was interrupted with message: {}", e.what());

    VAN_ENGINE_CRITICAL(message);
    if (e.showDialog()) {
      Dialogs::show("Application initialization interrupted.", message,
                    DialogType::Error);
    }
    this->_initializationInterrupted = true;
  } catch (const SubsystemInitializationException &e) {
    const std::string message = fmt::format(
        "Subsystem initialization errored with message: {}", e.what());

    VAN_ENGINE_CRITICAL(message);
    if (e.showDialog()) {
      Dialogs::show("Application initialization interrupted.", message,
                    DialogType::Error);
    }
    this->_initializationInterrupted = true;
  }
}

#pragma endregion

}  // namespace vanadium
