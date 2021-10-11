#pragma once

#include <vanadium/core/interfaces/ApplicationInitHook.h>
#include <vanadium/core/interfaces/constructed/factories/LoggerFactory.h>

class AppInitHook : public vanadium::ApplicationInitHook {
  vanadium::Ref<vanadium::Logger> _logger;

 public:
  explicit AppInitHook(vanadium::Ref<vanadium::LoggerFactory> loggerFactory);
  ~AppInitHook() override = default;

  void afterSubsystemInit(
      vanadium::EngineEndApplication *application,
      const vanadium::Ref<vanadium::Subsystem> &subsystem) override;
};
