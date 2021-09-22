#pragma once

#include "core/interfaces/MainLoop.h"

namespace vanadium {

class EngineEndApplication;
class EngineEndStateStack;
class EngineEndEventProvider;
class EventProvider;
class Stopwatch;

class MainLoopImpl : public EngineEndMainLoop {
 private:
  Ref<Stopwatch> _frameTime = nullptr;

  Ref<EngineEndStateStack> _stateStack = nullptr;
  Ref<EngineEndApplication> _application = nullptr;
  Ref<EngineEndEventProvider> _eventProvider = nullptr;

  size_t _ticksSinceStart = 0;
  size_t _fixedUpdateTicks = 0;
  float _deltatime = 1.0f;
  float _fixedUpdateTime = 1.0f / 60.0f;
  double _secondsSinceStart = 0.0;

  float _timeSinceLastFixedUpdate = 0.0;

 public:
  MainLoopImpl(Ref<EngineEndApplication> application,
               Ref<EngineEndStateStack> stateStack,
               Ref<EngineEndEventProvider> eventProvider);
  ~MainLoopImpl() override = default;

#pragma region EngineEndMainLoop

  void tick() override;
  void run() override;

#pragma endregion

#pragma region MainLoop

  void setFixedUpdateTime(float fixedUpdateTime) noexcept override;

  [[nodiscard]] float getDeltatime() const noexcept override;
  [[nodiscard]] float getFixedUpdateTime() const noexcept override;
  [[nodiscard]] double getSecondsSinceStart() const noexcept override;
  [[nodiscard]] std::size_t getTicksSinceStart() const noexcept override;
  [[nodiscard]] std::size_t getFixedUpdateTicks() const noexcept override;

  Ref<Application> getApplication() override;
  Ref<StateStack> getStateStack() override;
  Ref<EventProvider> getEventProvider() override;

#pragma endregion
};

}  // namespace vanadium