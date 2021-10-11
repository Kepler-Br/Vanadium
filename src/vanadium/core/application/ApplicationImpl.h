#pragma once

#include <string>
#include <unordered_map>

#include "vanadium/core/interfaces/Application.h"
#include "vanadium/core/interfaces/FactoryContainer.h"
#include "vanadium/core/interfaces/constructed/Logger.h"
#include "vanadium/core/types/Reference.h"
#include "vanadium/core/types/application/ApplicationProperties.h"

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
  Ref<ApplicationInitHook> _initHook = nullptr;
  Ref<Logger> _logger = nullptr;
  std::unordered_map<std::string, Ref<Subsystem>> _subsystems;

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
  [[nodiscard]] Ref<FactoryContainer> getFactoryContainer() noexcept override;
  [[nodiscard]] const ApplicationProperties &getProperties()
      const noexcept override;
  [[nodiscard]] Ref<Subsystem> getSubsystem(const std::string &name) override;
  void stop() override;

#pragma endregion

#pragma region EngineEndApplication

  void run() override;
  void setProperties(const ApplicationProperties &properties) override;
  void setInitializationHook(Ref<ApplicationInitHook> initHook) override;
  void addSubsystem(Ref<Subsystem> subsystem) override;
  void initialize() override;

  [[nodiscard]] Ref<EngineEndStateStack> getEngineStateStack() noexcept override;
  [[nodiscard]] Ref<EngineEndMainLoop> getEngineMainLoop() noexcept override;
  [[nodiscard]] Ref<EngineEndEventProvider> getEngineEventProvider() noexcept override;

  void pushState(Ref<State> state) override;

#pragma endregion
};

}  // namespace vanadium
