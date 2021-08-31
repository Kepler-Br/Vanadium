#pragma once

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <vector>

#include "BgfxCallback.h"
#include "core/interfaces/Subsystem.h"
#include "graphics/RendererApiEnum.h"

namespace vanadium {

class Window;

class BgfxSubsystem : public Subsystem {
 protected:
  Ref<Window> _window;

  BgfxCallback _bgfxCallback;

  RendererApi _preferredRenderApi = RendererApi::Any;

  RendererApi getRenderAccordingPriority(
      const std::vector<RendererApi>& renderApiPriority);

 public:
  explicit BgfxSubsystem(
      Ref<Window> mainWindow,
      const std::vector<RendererApi>& renderApiPriority = {});

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium
