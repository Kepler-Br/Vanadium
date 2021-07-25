#include "Application.h"

#include <core/subsystems/LoggingSubsystem.h>

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/subsystems/BgfxSubsystem.h"
#include "core/subsystems/SdlSubsystem.h"
#include "core/subsystems/VfsSubsystem.h"
#include "vfs/Vfs.h"

namespace vanadium {

void Application::tick() {
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
  this->_window->swapBuffer();
  this->_ticksSinceStart++;
  this->_secondsSinceStart += this->_deltatime;
  this->_timeSinceLastFixedUpdate += this->_deltatime;
}

Application::Application() {}

Application::~Application() {
  VAN_ENGINE_INFO("Destroying Application.");

  std::for_each(this->_subsystems.rbegin(), this->_subsystems.rend(),
                [](const auto &subsystem) { subsystem->shutdown(); });
}

void Application::run() {
  if (this->_initializationInterrupted) {
    VAN_ENGINE_INFO(
        "Initialization was interrupted. Application::run execution stopped.");
    return;
  }
  while (true) {
    if (this->_stateStack->size() == 0) break;
    try {
      this->tick();
    } catch (const ExecutionInterrupted &e) {
      std::string message =
          fmt::format("Execution interrupted with message: {}", e.what());
      VAN_ENGINE_CRITICAL(message);
      if (e.showDialog()) {
        bool result =
            Dialogs::show("Application error", message, DialogType::Error);
        if (!result) VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
      }
      this->_stateStack->popAll();
    }
  }
}

void Application::stop() noexcept { this->_stateStack->requestPopAll(); }

void Application::init(const ApplicationProperties &properties) {
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

    Ref<BgfxSubsystem> bgfxSubsystem = MakeRef<BgfxSubsystem>(this->_window);
    bgfxSubsystem->init();
    this->_subsystems.push_back(bgfxSubsystem);

    this->_eventProvider = EventProviderFactory::create();
    this->_frameTime = Stopwatch::create();
    this->_stateStack = MakeRef<StateStack>(this);
    this->postInit();
  } catch (InitializationInterrupted &e) {
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
  } catch (SubsystemInitializationException &e) {
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

void Application::setFixedUpdateTime(double newFixedUpdateTime) noexcept {
  this->_fixedUpdateTime = newFixedUpdateTime;
}

double Application::getDeltatime() const noexcept { return this->_deltatime; }

double Application::getFixedUpdateTime() const noexcept {
  return this->_fixedUpdateTime;
}

double Application::getSecondsSinceStart() const noexcept {
  return this->_secondsSinceStart;
}

Ref<Window> Application::getWindow() const noexcept { return this->_window; }

size_t Application::getTicksSinceStart() const noexcept {
  return this->_ticksSinceStart;
}

size_t Application::getFixedUpdateTicks() const noexcept {
  return this->_fixedUpdateTicks;
}

const std::vector<std::string> &Application::getProgramArguments()
    const noexcept {
  return this->_programArguments;
}

Ref<UserEndEventProvider> Application::getEventProvider() const noexcept {
  return this->_eventProvider;
}

Ref<UserEndStateStack> Application::getStateStack() const noexcept {
  return this->_stateStack;
}

}  // namespace vanadium