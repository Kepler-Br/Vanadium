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
 private:
  Ref<EngineEndEventProvider> _eventProvider = nullptr;
  Ref<EngineEndStateStack> _stateStack = nullptr;
  Ref<Window> _window = nullptr;
  Ref<EngineEndMainLoop> _mainLoop = nullptr;
  std::vector<Ref<Subsystem>> _subsystems;

  ApplicationProperties _properties;

  bool _initializationInterrupted = false;

  void initializeSubsystemByStage(std::size_t stage);

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
  [[nodiscard]] const ApplicationProperties &getProperties()
      const noexcept override;

#pragma endregion

#pragma region EngineEndApplication

  void run() override;

  void setProperties(const ApplicationProperties &properties) override;

#pragma endregion
};

}  // namespace vanadium
