#include "ApplicationImpl.h"

#include <SDL_error.h>
#include <core/subsystems/LoggingSubsystem.h>

#include <utility>

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/interfaces/EventProvider.h"
#include "core/interfaces/MainLoop.h"
#include "core/interfaces/StateStack.h"
#include "core/subsystems/BgfxSubsystem.h"
#include "core/subsystems/SdlSubsystem.h"
#include "core/subsystems/VfsSubsystem.h"

namespace vanadium {

ApplicationImpl::ApplicationImpl(Ref<EngineEndMainLoop> mainLoop,
                                 Ref<EngineEndStateStack> stateStack,
                                 Ref<EngineEndEventProvider> eventProvider,
                                 Ref<Window> window)
    : _eventProvider(std::move(eventProvider)),
      _stateStack(std::move(stateStack)),
      _window(std::move(window)),
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

const std::vector<std::string> &ApplicationImpl::getProgramArguments()
    const noexcept {
  return this->_programArguments;
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
      bool result =
          Dialogs::show("Application error", message, DialogType::Error);
      if (!result) {
        VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
      }
    }
    this->_stateStack->popAll();
  }
}

void ApplicationImpl::preInit() {
  // noop.
}
void ApplicationImpl::postInit() {
  // noop.
}

void ApplicationImpl::setProperties(const ApplicationProperties &properties) {
  try {
    Ref<LoggingSubsystem> loggingSubsystem = MakeRef<LoggingSubsystem>(
        properties.getLogLevel(), properties.getWriteLogToDisc(),
        properties.getLogPath());

    loggingSubsystem->init();
    this->_subsystems.push_back(loggingSubsystem);

    VAN_ENGINE_INFO("Initializing Application.");

    this->_programArguments = properties.getArguments();

    Ref<VfsSubsystem> vfsSubsystem =
        MakeRef<VfsSubsystem>(this->_programArguments[0]);
    vfsSubsystem->init();
    this->_subsystems.push_back(vfsSubsystem);

    this->preInit();

    Ref<SdlSubsystem> sdlSubsystem = MakeRef<SdlSubsystem>();
    sdlSubsystem->init();
    this->_subsystems.push_back(sdlSubsystem);

    this->_window = Window::create(properties.getWindowProperties());

    Ref<BgfxSubsystem> bgfxSubsystem = MakeRef<BgfxSubsystem>(
        this->_window, properties.getRenderApiPriority());
    bgfxSubsystem->init();
    this->_subsystems.push_back(bgfxSubsystem);

    this->postInit();
  } catch (const InitializationInterrupted &e) {
    const std::string message = fmt::format(
        "Initialization was interrupted with message: {}", e.what());

    VAN_ENGINE_CRITICAL(message);
    if (e.showDialog()) {
      bool result = Dialogs::show("Application initialization interrupted.",
                                  message, DialogType::Error);
      if (!result) {
        VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
      }
    }
    this->_initializationInterrupted = true;
  } catch (const SubsystemInitializationException &e) {
    const std::string message = fmt::format(
        "Initialization was interrupted with message: {}", e.what());

    VAN_ENGINE_CRITICAL(message);
    if (e.showDialog()) {
      bool result = Dialogs::show("Application initialization interrupted.",
                                  message, DialogType::Error);
      if (!result) {
        VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
      }
    }
    this->_initializationInterrupted = true;
  }
}

#pragma endregion

}  // namespace vanadium
