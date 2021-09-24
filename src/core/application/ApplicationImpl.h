#pragma once

#include <string>

#include "core/application/FactoryContainer.h"
#include "core/interfaces/Application.h"
#include "core/types/Reference.h"
#include "core/types/application/ApplicationProperties.h"

namespace vanadium {

class EngineEndMainLoop;
class EngineEndEventProvider;
class EngineEndStateStack;
class EventProvider;
class MainLoop;
class Subsystem;
class Window;

class ApplicationImpl : public EngineEndApplication {
 private:
  Ref<EngineEndEventProvider> _eventProvider = nullptr;
  Ref<EngineEndStateStack> _stateStack = nullptr;
  Ref<Window> _window = nullptr;
  Ref<EngineEndMainLoop> _mainLoop = nullptr;
  Ref<FactoryContainer> _factoryContainer = nullptr;
  std::vector<Ref<Subsystem>> _subsystems;

  ApplicationProperties _properties;

  bool _initializationInterrupted = false;

  const std::size_t _subsystemStages = 3;

  void initializeSubsystemByStage(std::size_t stage);
  void deinitializeSubsystemByStage(std::size_t stage);

 public:
  ApplicationImpl(Ref<EngineEndMainLoop> mainLoop,
                  Ref<EngineEndStateStack> stateStack,
                  Ref<EngineEndEventProvider> eventProvider,
                  Ref<FactoryContainer> factoryContainer);
  ~ApplicationImpl() override;

#pragma region Application

  [[nodiscard]] Ref<EventProvider> getEventProvider() noexcept override;
  [[nodiscard]] Ref<Window> getWindow() noexcept override;
  [[nodiscard]] Ref<StateStack> getStateStack() noexcept override;
  [[nodiscard]] Ref<MainLoop> getMainLoop() noexcept override;
  void stop() override;
  [[nodiscard]] const ApplicationProperties &getProperties()
      const noexcept override;

#pragma endregion

#pragma region EngineEndApplication

  void run() override;

  void setProperties(const ApplicationProperties &properties) override;

  void addSubsystem(Ref<Subsystem> subsystem) override;

  void initializeSubsystems() override;

#pragma endregion
};

}  // namespace vanadium
