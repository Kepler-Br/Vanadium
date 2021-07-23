#include "core/Application.h"

#include "core/Dialogs.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "vfs/Vfs.h"

namespace vanadium {

void Application::initVfs() {
  if (!vfs::init(this->programArguments[0])) {
    throw InitializationInterrupted(
        fmt::format("Unable to initialize VFS: \"{}\"", vfs::getError()),
        false);
  }
}

void Application::tick() {
  State *topState;

  this->deltatime = this->frameTime->stop();
  this->frameTime->start();
  topState = this->stateStack->top();
  this->eventProvider->dispatch();
  this->eventProvider->update();
  topState->onTickStart();
  topState->update(this->deltatime);
  while (this->timeSinceLastFixedUpdate > this->fixedUpdateTime) {
    topState->fixedUpdate(this->fixedUpdateTime);
    this->timeSinceLastFixedUpdate -= this->fixedUpdateTime;
    this->fixedUpdateTicks++;
  }
  topState->preRender();
  topState->render();
  topState->postRender();
  topState->onTickEnd();
  this->stateStack->executeCommands();
  this->window->swapBuffer();
  this->ticksSinceStart++;
  this->secondsSinceStart += this->deltatime;
  this->timeSinceLastFixedUpdate += this->deltatime;
}

Application::Application() {
  Log::init();
}

Application::~Application() {
  VAN_ENGINE_INFO("Destroying Application.");
  vfs::deinit();
  delete this->bgfxContext;
  delete this->eventProvider;
  delete this->window;
  delete this->stateStack;
  delete this->frameTime;
}

void Application::run() {
  if (this->initializationInterrupted) {
    VAN_ENGINE_INFO(
        "Initialization was interrupted. Application::run execution stopped.");
    return;
  }
  while (true) {
    if (this->stateStack->size() == 0) break;
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
      this->stateStack->popAll();
    }
  }
}

void Application::stop() noexcept { this->stateStack->requestPopAll(); }

void Application::init(const ApplicationProperties &properties) {
  VAN_ENGINE_INFO("Initializing Application.");
  try {
    this->programArguments = properties.getArguments();
    this->initVfs();
    this->preInit();
    this->window = Window::create(properties.getWindowProperties());
    this->bgfxContext = new BgfxContext(this->window);
    this->eventProvider = EventProviderFactory::create(this->window);
    this->frameTime = Stopwatch::create();
    this->stateStack = new StateStack(this);
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
    this->initializationInterrupted = true;
  }
}

void Application::setFixedUpdateTime(double newFixedUpdateTime) noexcept {
  this->fixedUpdateTime = newFixedUpdateTime;
}

double Application::getDeltatime() const noexcept { return this->deltatime; }

double Application::getFixedUpdateTime() const noexcept {
  return this->fixedUpdateTime;
}

double Application::getSecondsSinceStart() const noexcept {
  return this->secondsSinceStart;
}

Window *Application::getWindow() const noexcept { return this->window; }

size_t Application::getTicksSinceStart() const noexcept {
  return this->ticksSinceStart;
}

size_t Application::getFixedUpdateTicks() const noexcept {
  return this->fixedUpdateTicks;
}

const std::vector<std::string> &Application::getProgramArguments()
    const noexcept {
  return this->programArguments;
}

UserEndEventProvider *Application::getEventProvider() const noexcept {
  return this->eventProvider;
}

UserEndStateStack *Application::getStateStack() const noexcept {
  return this->stateStack;
}

}  // namespace vanadium