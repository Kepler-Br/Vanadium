#include "BgfxContext.h"

#include "core/Exceptions.h"
#include "core/Window.h"

namespace vanadium {

BgfxContext::BgfxContext(Window *window) : _window(window) {
  bgfx::Init init;

  init.platformData.ndt = this->_window->getNativeDisplayType();
  init.platformData.nwh = this->_window->getNativeWindowHandle();
  init.resolution.width = this->_window->getGeometry().x;
  init.resolution.height = this->_window->getGeometry().y;
  init.resolution.reset = BGFX_RESET_NONE;
  init.callback = &this->bgfxCallback;
  this->_resetFlags = init.resolution.reset;
  if (!bgfx::init(init)) {
    const std::string message = "Error initializing bgfx.";
    VAN_ENGINE_CRITICAL(message);
    throw InitializationInterrupted(message);
  }

  const bgfx::ViewId mainView = 0;
  bgfx::setViewClear(mainView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
  bgfx::setViewRect(mainView, 0, 0, bgfx::BackbufferRatio::Equal);
}

BgfxContext::~BgfxContext() {
  bgfx::shutdown();
}

void BgfxContext::reset(const glm::ivec2 &resolution) {
  bgfx::reset((uint32_t)resolution.x, (uint32_t)resolution.y, this->_resetFlags,
              this->_format);
}

void BgfxContext::reset(const glm::ivec2 &resolution, uint32_t resetFlags,
                        bgfx::TextureFormat::Enum format) {
  this->_resetFlags = resetFlags;
  this->_format = format;

  bgfx::reset((uint32_t)resolution.x, (uint32_t)resolution.y, resetFlags,
              format);
}

}  // namespace vanadium