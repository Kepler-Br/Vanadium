#include "ApplicationImpl.h"

#include <fmt/format.h>

#include <utility>

#include "vanadium/core/Dialogs.h"
#include "vanadium/core/Exceptions.h"
#include "vanadium/core/interfaces/EventProvider.h"
#include "vanadium/core/interfaces/MainLoop.h"
#include "vanadium/core/interfaces/StateStack.h"
#include "vanadium/core/interfaces/Subsystem.h"
#include "vanadium/core/interfaces/constructed/factories/LoggerFactory.h"
#include "vanadium/core/interfaces/constructed/factories/WindowFactory.h"

namespace vanadium {

#pragma region private

void ApplicationImpl::initializeSubsystemByStage(std::size_t stage) {
  this->_logger->trace(fmt::format("Initializing subsystem stage {}", stage));

  if (this->_initHook != nullptr) {
    this->_initHook->preSubsystemStage(this, stage);
    for (const auto &subsystem : this->_subsystems) {
      if (subsystem->getInitializationStage() == stage) {
        this->_logger->trace(
            fmt::format("Initializing subsystem {}", subsystem->getName()));

        this->_initHook->preSubsystemInit(this, subsystem);
        subsystem->initialize(this);
        this->_initHook->afterSubsystemInit(this, subsystem);
      }
    }
    this->_initHook->afterSubsystemStage(this, stage);
  } else {
    for (const auto &subsystem : this->_subsystems) {
      if (subsystem->getInitializationStage() == stage) {
        this->_logger->trace(
            fmt::format("Initializing subsystem {}", subsystem->getName()));

        subsystem->initialize(this);
      }
    }
  }
}

void ApplicationImpl::deinitializeSubsystemByStage(std::size_t stage) {
  this->_logger->trace(fmt::format("Deinitializing subsystem stage {}", stage));

  for (const auto &subsystem : this->_subsystems) {
    if (subsystem->getInitializationStage() == stage) {
      this->_logger->trace(
          fmt::format("Deinitializing subsystem {}", subsystem->getName()));
      subsystem->deinitialize();
    }
  }
}

#pragma endregion

ApplicationImpl::ApplicationImpl(Ref<EngineEndMainLoop> mainLoop,
                                 Ref<EngineEndStateStack> stateStack,
                                 Ref<EngineEndEventProvider> eventProvider,
                                 Ref<FactoryContainer> factoryContainer)
    : _eventProvider(std::move(eventProvider)),
      _stateStack(std::move(stateStack)),
      _mainLoop(std::move(mainLoop)),
      _factoryContainer(std::move(factoryContainer)) {
  Ref<LoggerFactory> loggerFactory =
      FactoryContainer::getFactory<LoggerFactory>(this->_factoryContainer);
  this->_logger = loggerFactory->construct("Application");
}

ApplicationImpl::~ApplicationImpl() {
  this->_logger->info("Destroying Application.");

  for (std::size_t stage = this->_subsystemStages - 1; stage != 0; stage--) {
    this->deinitializeSubsystemByStage(stage);
  }
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

Ref<FactoryContainer> ApplicationImpl::getFactoryContainer() noexcept {
  return this->_factoryContainer;
}

const ApplicationProperties &ApplicationImpl::getProperties() const noexcept {
  return this->_properties;
}

void ApplicationImpl::stop() { this->_stateStack->requestPopAll(); }

#pragma endregion

#pragma region EngineEndApplication

void ApplicationImpl::run() {
  if (this->_initializationInterrupted) {
    this->_logger->error(
        "Initialization was interrupted. "
        "ApplicationImpl::run execution stopped.");

    return;
  }

  try {
    this->_mainLoop->run();
  } catch (const ExecutionInterrupted &e) {
    std::string message =
        fmt::format("Execution interrupted with message: {}", e.what());

    this->_logger->critical(message);

    if (e.showDialog()) {
      Dialogs::show("Application error", message, DialogType::Error);
    }

    this->_stateStack->popAll();
  }
}

void ApplicationImpl::setProperties(const ApplicationProperties &properties) {
  this->_properties = properties;
}

void ApplicationImpl::setInitializationHook(Ref<ApplicationInitHook> initHook) {
  this->_initHook = std::move(initHook);
}

void ApplicationImpl::addSubsystem(Ref<Subsystem> subsystem) {
  this->_subsystems.push_back(std::move(subsystem));
}

void ApplicationImpl::initialize() {
  this->_logger->trace("Initializing application.");

  std::vector<std::size_t> subsystemsPerStage;

  subsystemsPerStage.resize(this->_subsystemStages, 0);

  for (const auto &subsystem : this->_subsystems) {
    std::size_t subsystemStage = subsystem->getInitializationStage();

    if (subsystemStage >= subsystemsPerStage.size()) {
      subsystemsPerStage.back()++;
    } else {
      subsystemsPerStage[subsystemStage]++;
    }
  }

  try {
    if (this->_initHook != nullptr) {
      this->_initHook->preInit(this);
    }

    if (subsystemsPerStage[0] != 0) {
      this->initializeSubsystemByStage(0);
    }

    if (subsystemsPerStage[1] != 0) {
      this->initializeSubsystemByStage(1);
    }

    Ref<WindowFactory> windowFactory =
        FactoryContainer::getFactory<WindowFactory>(this->_factoryContainer);
    this->_window =
        windowFactory->construct(this->_properties.getWindowProperties());

    for (std::size_t stage = 2; stage < this->_subsystemStages; stage++) {
      if (subsystemsPerStage[stage] != 0) {
        this->initializeSubsystemByStage(stage);
      }
    }

    if (this->_initHook != nullptr) {
      this->_initHook->afterInit(this);
    }

    this->_logger->trace("Done initializing application.");
  } catch (const InitializationInterrupted &e) {
    const std::string message = fmt::format(
        "Initialization was interrupted with message: {}", e.what());

    this->_logger->critical(message);

    if (e.showDialog()) {
      Dialogs::show("Application initialization interrupted.", message,
                    DialogType::Error);
    }
    this->_initializationInterrupted = true;
  } catch (const SubsystemInitializationException &e) {
    const std::string message = fmt::format(
        "Subsystem initialization errored with message: {}", e.what());

    this->_logger->critical(message);

    if (e.showDialog()) {
      Dialogs::show("Application initialization interrupted.", message,
                    DialogType::Error);
    }
    this->_initializationInterrupted = true;
  }
}

#pragma endregion

}  // namespace vanadium
