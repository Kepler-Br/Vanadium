#include "MainState.h"

void MainState::setupEvents() {
  using namespace vanadium;

  this->eventDispatcher->subscribe(
      Event::Type::MouseMove,
      [this](Event *event) { this->onMouseMove((MouseMoveEvent *)event); });
  this->eventDispatcher->subscribe(
      Event::Type::WindowClose,
      [this](Event *event) { this->onWindowClose((WindowCloseEvent *)event); });
  this->eventDispatcher->subscribe(
      Event::Type::KeyPressed,
      [this](Event *event) { this->onKeyPressed((KeyPressedEvent *)event); });
}

void MainState::onMouseMove(vanadium::MouseMoveEvent *event) {}

void MainState::onWindowClose(vanadium::WindowCloseEvent *event) {
  this->stateStack->requestPopAll();
}

void MainState::onKeyPressed(vanadium::KeyPressedEvent *event) {
  if (event->getKeyCode() == vanadium::keyboard::KeyCode::Escape) {
    this->stateStack->requestPopAll();
  }
  if (event->getKeyCode() == vanadium::keyboard::KeyCode::F1) {
    this->showDebugStats = !this->showDebugStats;
    bgfx::setDebug(this->showDebugStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_NONE);
  }
}

MainState::MainState() {}

MainState::~MainState() {}

void MainState::onAttach(vanadium::StateEndApplication *application,
                         const std::string &name) {
  this->setupEvents();
}

void MainState::onDetach() {}

void MainState::onStateLostPriority() {}

void MainState::onStateGainedPriority() { this->setupEvents(); }

void MainState::loadResources(const std::function<void()> &callback) {}

void MainState::loadResources() {}

void MainState::onTickStart() {}

void MainState::onTickEnd() {}

void MainState::update(double deltatime) {}

void MainState::fixedUpdate(double deltatime) {}

void MainState::preRender() {}

void MainState::render() {
  // This dummy draw call is here to make sure that view 0 is cleared if no
  // other draw calls are submitted to view 0.
  bgfx::touch(0);
  // Use debug font to print information about this example.
  bgfx::dbgTextClear();
  bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
  bgfx::dbgTextPrintf(0, 1, 0x0f,
                      "Color can be changed with ANSI "
                      "\x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b["
                      "14;me\x1b[0m code too.");
  bgfx::dbgTextPrintf(
      80, 1, 0x0f,
      "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; "
      "5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
  bgfx::dbgTextPrintf(
      80, 2, 0x0f,
      "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    "
      "\x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
  const bgfx::Stats *stats = bgfx::getStats();
  bgfx::dbgTextPrintf(
      0, 2, 0x0f,
      "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
      stats->width, stats->height, stats->textWidth, stats->textHeight);
  // Enable stats or debug text.
  // Advance to next frame. Process submitted rendering primitives.
  bgfx::frame();
}
void MainState::postRender() {}

const std::string &MainState::getName() const noexcept { return this->name; }
