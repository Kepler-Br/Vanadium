#include "BgfxSubsystem.h"

#include <unordered_set>
#include <utility>

#include "core/Exceptions.h"
#include "core/interfaces/Application.h"
#include "core/interfaces/constructed/Window.h"
#include "core/types/application/ApplicationProperties.h"

namespace vanadium {

#pragma region private

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

#pragma endregion

#pragma region public

BgfxSubsystem::BgfxSubsystem() : _name("bgfx"), _initializationStage(2) {}

BgfxSubsystem::BgfxSubsystem(std::string name, std::size_t initializationStage)
    : _name(std::move(name)), _initializationStage(initializationStage) {}

const std::string& BgfxSubsystem::getName() const noexcept { return _name; }

void BgfxSubsystem::initialize(EngineEndApplication* application) {
  Ref<Window> window = application->getWindow();

  bgfx::Init init;

  init.platformData.ndt = window->getNativeDisplayType();
  init.platformData.nwh = window->getNativeWindowHandle();
  init.resolution.width = window->getGeometry().x;
  init.resolution.height = window->getGeometry().y;
  init.resolution.reset = BGFX_RESET_NONE;
  init.callback = &this->_bgfxCallback;

  auto& renderPriority = application->getProperties().getRenderApiPriority();

  RendererApi preferredRenderApi = getRenderAccordingPriority(renderPriority);

  if (preferredRenderApi == RendererApi::Undefined ||
      preferredRenderApi == RendererApi::Noop) {
    const std::string message =
        "Renderer API is undefined. Possibly that requested APIs are not "
        "supported by current system.";

    throw SubsystemInitializationException(message);
  } else if (preferredRenderApi != RendererApi::Any) {
    init.type = rendererApiToBgfxType(preferredRenderApi);
  }

  if (!bgfx::init(init)) {
    const std::string message = "Error initializing bgfx.";

    throw SubsystemInitializationException(message);
  }

  const bgfx::ViewId mainView = 0;
  bgfx::setViewClear(mainView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
  bgfx::setViewRect(mainView, 0, 0, bgfx::BackbufferRatio::Equal);

  this->_initialized = true;
}

void BgfxSubsystem::deinitialize() {
  bgfx::shutdown();

  this->_initialized = false;
}

std::size_t BgfxSubsystem::getInitializationStage() const noexcept {
  return this->_initializationStage;
}

bool BgfxSubsystem::isInitialized() const noexcept {
  return this->_initialized;
}

#pragma endregion

}  // namespace vanadium
