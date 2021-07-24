#include "BgfxSubsystem.h"

#include <utility>

#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/Window.h"

namespace vanadium {

BgfxSubsystem::BgfxSubsystem(Ref<Window> mainWindow)
    : Subsystem("BGFX"), _window(std::move(mainWindow)) {}

void BgfxSubsystem::init() {
  VAN_ENGINE_TRACE("Initializing BGFX subsystem.");

  bgfx::Init init;

  init.platformData.ndt = this->_window->getNativeDisplayType();
  init.platformData.nwh = this->_window->getNativeWindowHandle();
  init.resolution.width = this->_window->getGeometry().x;
  init.resolution.height = this->_window->getGeometry().y;
  init.resolution.reset = BGFX_RESET_NONE;
  init.callback = &this->_bgfxCallback;
  if (!bgfx::init(init)) {
    const std::string message = "Error initializing bgfx.";

    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }

  const bgfx::ViewId mainView = 0;
  bgfx::setViewClear(mainView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
  bgfx::setViewRect(mainView, 0, 0, bgfx::BackbufferRatio::Equal);
}

void BgfxSubsystem::shutdown() {
  VAN_ENGINE_TRACE("Shutting down BGFX subsystem.");
  bgfx::shutdown();
}

}  // namespace vanadium