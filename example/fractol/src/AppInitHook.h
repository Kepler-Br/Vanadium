#pragma once

#include <core/interfaces/ApplicationInitHook.h>

class AppInitHook : public vanadium::ApplicationInitHook {
 public:
  ~AppInitHook() override = default;

  void afterSubsystemInit(
      vanadium::EngineEndApplication *application,
      const vanadium::Ref<vanadium::Subsystem> &subsystem) override;
};
