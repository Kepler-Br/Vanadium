#pragma once

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>
#include <vector>

#include "BgfxCallback.h"
#include "core/interfaces/Subsystem.h"

namespace vanadium {

class Window;

class BgfxSubsystem : public Subsystem {
 protected:
  Ref<Window> _window;

  BgfxCallback _bgfxCallback;

  bgfx::RendererType::Enum _preferedRenderApi = bgfx::RendererType::Enum::Noop;

  bgfx::RendererType::Enum getRenderAccordingPriority(
      const std::vector<bgfx::RendererType::Enum>& renderApiPriority);

 public:
  explicit BgfxSubsystem(
      Ref<Window> mainWindow,
      const std::vector<bgfx::RendererType::Enum>& renderApiPriority = {});

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium
