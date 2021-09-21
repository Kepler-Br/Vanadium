#include "ApplicationImpl.h"

#include <core/subsystems/LoggingSubsystem.h>

#include <utility>

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/interfaces/MainLoop.h"
#include "core/subsystems/BgfxSubsystem.h"
#include "core/subsystems/SdlSubsystem.h"
#include "core/subsystems/VfsSubsystem.h"
#include "vfs/Vfs.h"

namespace vanadium {


ApplicationImpl::ApplicationImpl(Ref<EngineEndMainLoop> mainLoop,
                Ref<StateStack> stateStack,
                Ref<EventProvider> eventProvider,
                Ref<Window> window) :
_mainLoop(mainLoop),
_stateStack(stateStack),
_eventProvider(eventProvider),
_window(window) {

}

ApplicationImpl::~ApplicationImpl() {
  VAN_ENGINE_INFO("Destroying Application.");

  std::for_each(this->_subsystems.rbegin(), this->_subsystems.rend(),
                [](const auto &subsystem) { subsystem->shutdown(); });
}

void ApplicationImpl::deinitialize() {
  this->_mainLoop = nullptr;
  this->_stateStack = nullptr;
  this->_eventProvider = nullptr;
  this->_window = nullptr;
}

void ApplicationImpl::run() {
  if (this->_initializationInterrupted) {
    VAN_ENGINE_INFO(
        "Initialization was interrupted. ApplicationImpl::run execution "
        "stopped.");
    return;
  }

  this->_mainLoop->run();
}

void ApplicationImpl::stop() { this->_stateStack->requestPopAll(); }

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

Ref<Window> ApplicationImpl::getWindow() const noexcept {
  return this->_window;
}

const std::vector<std::string> &ApplicationImpl::getProgramArguments()
    const noexcept {
  return this->_programArguments;
}

Ref<UserEndEventProvider> ApplicationImpl::getEventProvider() const noexcept {
  return this->_eventProvider;
}

Ref<UserEndStateStack> ApplicationImpl::getStateStack() const noexcept {
  return this->_stateStack;
}

}  // namespace vanadium