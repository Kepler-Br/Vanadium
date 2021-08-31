#include "BgfxSubsystem.h"

#include <unordered_set>
#include <utility>

#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/Window.h"

namespace vanadium {

RendererApi BgfxSubsystem::getRenderAccordingPriority(
    const std::vector<RendererApi>& renderApiPriority) {
  if (renderApiPriority.empty()) {
    return RendererApi::Any;
  }

  std::vector<bgfx::RendererType::Enum> supportedRenderers;
  std::uint8_t numSupportedRenderers = bgfx::getSupportedRenderers();

  supportedRenderers.resize(numSupportedRenderers);
  bgfx::getSupportedRenderers(numSupportedRenderers, supportedRenderers.data());

  std::unordered_set<bgfx::RendererType::Enum> supportedRenderersSet(
      supportedRenderers.begin(), supportedRenderers.end());

  for (const auto& api : renderApiPriority) {
    const bgfx::RendererType::Enum apiToFind = rendererApiToBgfxType(api);

    if (supportedRenderersSet.find(apiToFind) != supportedRenderersSet.end()) {
      return api;
    }
  }

  return RendererApi::Undefined;
}

BgfxSubsystem::BgfxSubsystem(Ref<Window> mainWindow,
                             const std::vector<RendererApi>& renderApiPriority)
    : Subsystem("BGFX"), _window(std::move(mainWindow)) {
  this->_preferredRenderApi = getRenderAccordingPriority(renderApiPriority);
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

  if (this->_preferredRenderApi == RendererApi::Undefined ||
      this->_preferredRenderApi == RendererApi::Noop) {
    const std::string message =
        "Renderer API is undefined. Possibly that requested APIs are not "
        "supported by current system.";

    VAN_ENGINE_CRITICAL(message);

    throw SubsystemInitializationException(message);
  } else if (this->_preferredRenderApi != RendererApi::Any) {
    init.type = rendererApiToBgfxType(this->_preferredRenderApi);
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