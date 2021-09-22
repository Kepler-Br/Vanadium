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
 private:
  std::string _name;
  std::size_t _initializationStage;

  BgfxCallback _bgfxCallback;

  static RendererApi getRenderAccordingPriority(
      const std::vector<RendererApi> &renderApiPriority);

 public:
  /**
   * Defaults name to BGFX and initializationStage to 2.
   */
  BgfxSubsystem();
  BgfxSubsystem(std::string name, std::size_t initializationStage);

  ~BgfxSubsystem() override = default;

  void initialize(EngineEndApplication &application) override;
  void deinitialize() override;

  [[nodiscard]] const std::string &getName() const noexcept override;

  [[nodiscard]] std::size_t getInitializationStage() const noexcept override;
};

}  // namespace vanadium
