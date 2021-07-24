#include "Application.h"

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "vfs/Vfs.h"

namespace vanadium {

void Application::initVfs() {
  if (!vfs::init(this->_programArguments[0])) {
    throw InitializationInterrupted(
        fmt::format("Unable to initialize VFS: \"{}\"", vfs::getError()));
  }
}

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

Application::Application() { Log::init(); }

Application::~Application() {
  VAN_ENGINE_INFO("Destroying Application.");
  vfs::deinit();
  delete this->_bgfxContext;
  delete this->_eventProvider;
  delete this->_window;
  delete this->_stateStack;
  delete this->_frameTime;
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
      VAN_ENGINE_CRITICAL("Execution interrupted with message: {}", e.what());
      if (e.showDialog()) {
        bool result = Dialogs::show(
            "In state error",
            std::string("Execution interrupted with message: ") + e.what(),
            DialogType::Error);
        if (!result) VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
      }
      this->_stateStack->popAll();
    }
  }
}

void Application::stop() noexcept { this->_stateStack->requestPopAll(); }

void Application::init(const ApplicationProperties &properties) {
  VAN_ENGINE_INFO("Initializing Application.");
  try {
    this->_programArguments = properties.getArguments();
    this->initVfs();
    this->preInit();
    this->_window = Window::create(properties.getWindowProperties());
    this->_bgfxContext = new BgfxContext(this->_window);
    this->_eventProvider = EventProviderFactory::create(this->_window);
    this->_frameTime = Stopwatch::create();
    this->_stateStack = new StateStack(this);
    this->postInit();
  } catch (const InitializationInterrupted &e) {
    VAN_ENGINE_INFO("Initialization was interrupted with message: {}",
                    e.what());
    if (e.showDialog()) {
      bool result = Dialogs::show(
          "Application initialization interrupted.",
          std::string("Execution interrupted with message: ") + e.what(),
          DialogType::Error);
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

Window *Application::getWindow() const noexcept { return this->_window; }

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

UserEndEventProvider *Application::getEventProvider() const noexcept {
  return this->_eventProvider;
}

UserEndStateStack *Application::getStateStack() const noexcept {
  return this->_stateStack;
}

}  // namespace vanadium