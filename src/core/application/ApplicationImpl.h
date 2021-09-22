#pragma once

#include <string>

#include "ApplicationProperties.h"
#include "core/Types.h"
#include "core/interfaces/Application.h"

namespace vanadium {

class EngineEndMainLoop;
class EngineEndEventProvider;
class EngineEndStateStack;
class EventProvider;
class MainLoop;
class Subsystem;

class ApplicationImpl : public EngineEndApplication {
 protected:
  Ref<EngineEndEventProvider> _eventProvider = nullptr;
  Ref<EngineEndStateStack> _stateStack = nullptr;
  Ref<Window> _window = nullptr;
  Ref<EngineEndMainLoop> _mainLoop = nullptr;
  std::vector<Ref<Subsystem>> _subsystems;

  std::vector<std::string> _programArguments;

  ApplicationProperties _properties;

  bool _initializationInterrupted = false;

 public:
  ApplicationImpl(Ref<EngineEndMainLoop> mainLoop,
                  Ref<EngineEndStateStack> stateStack,
                  Ref<EngineEndEventProvider> eventProvider);
  ~ApplicationImpl() override;

#pragma region Application

  [[nodiscard]] Ref<EventProvider> getEventProvider() noexcept override;
  [[nodiscard]] Ref<Window> getWindow() noexcept override;
  [[nodiscard]] Ref<StateStack> getStateStack() noexcept override;
  [[nodiscard]] Ref<MainLoop> getMainLoop() noexcept override;
  void stop() override;
  [[nodiscard]] const std::vector<std::string> &getProgramArguments()
      const noexcept override;

  [[nodiscard]] const ApplicationProperties &getApplicationProperties()
      const noexcept override;

#pragma endregion

#pragma region EngineEndApplication

  void run() override;

  void preInit() override;
  void postInit() override;

  void setProperties(const ApplicationProperties &properties) override;

#pragma endregion
};

}  // namespace vanadium