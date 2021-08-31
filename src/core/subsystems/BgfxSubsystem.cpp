#include "BgfxSubsystem.h"

#include <unordered_set>
#include <utility>

#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/Window.h"

namespace vanadium {

bgfx::RendererType::Enum BgfxSubsystem::getRenderAccordingPriority(
    const std::vector<bgfx::RendererType::Enum>& renderApiPriority) {
  if(renderApiPriority.empty()) {
    return bgfx::RendererType::Enum::Noop;
  }

  std::vector<bgfx::RendererType::Enum> supportedRenderers;
  std::uint8_t numSupportedRenderers = bgfx::getSupportedRenderers();

  supportedRenderers.resize(numSupportedRenderers);
  bgfx::getSupportedRenderers(numSupportedRenderers, supportedRenderers.data());

  std::unordered_set<bgfx::RendererType::Enum> supportedRenderersSet(
      supportedRenderers.begin(), supportedRenderers.end());

  for (const auto& api : renderApiPriority) {
    if (supportedRenderersSet.find(api) != supportedRenderersSet.end()) {
      return api;
    }
  }

  return bgfx::RendererType::Enum::Noop;
}

BgfxSubsystem::BgfxSubsystem(
    Ref<Window> mainWindow,
    const std::vector<bgfx::RendererType::Enum>& renderApiPriority)
    : Subsystem("BGFX"), _window(std::move(mainWindow)) {
  this->_preferedRenderApi = getRenderAccordingPriority(renderApiPriority);
}

void BgfxSubsystem::init() {
  VAN_ENGINE_TRACE("Initializing BGFX subsystem.");

  bgfx::Init init;

  init.platformData.ndt = this->_window->getNativeDisplayType();
  init.platformData.nwh = this->_window->getNativeWindowHandle();
  init.resolution.width = this->_window->getGeometry().x;
  init.resolution.height = this->_window->getGeometry().y;
  init.resolution.reset = BGFX_RESET_NONE;
  init.callback = &this->_bgfxCallback;

  if (this->_preferedRenderApi != bgfx::RendererType::Enum::Noop) {
    init.type = this->_preferedRenderApi;
  }

  if (!bgfx::init(init)) {
    const std::string message = "Error initializing bgfx.";

    VAN_ENGINE_CRITICAL(message);
    throw SubsystemInitializationException(message);
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