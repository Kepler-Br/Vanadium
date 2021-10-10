#pragma once

#include "vanadium/core/interfaces/MainLoop.h"
#include "vanadium/core/interfaces/constructed/Logger.h"

namespace vanadium {

class EngineEndApplication;
class EngineEndStateStack;
class EngineEndEventProvider;
class FactoryContainer;
class Stopwatch;

class MainLoopImpl : public EngineEndMainLoop {
 private:
  Ref<Stopwatch> _frameTime = nullptr;
  Ref<Logger> _logger = nullptr;

  Ref<EngineEndStateStack> _stateStack = nullptr;
  Ref<EngineEndEventProvider> _eventProvider = nullptr;
  Ref<FactoryContainer> _factoryContainer = nullptr;

  size_t _ticksSinceStart = 0;
  size_t _fixedUpdateTicks = 0;
  float _deltaTime = 1.0f;
  float _fixedUpdateTime = 1.0f / 60.0f;
  double _secondsSinceStart = 0.0;

  float _timeSinceLastFixedUpdate = 0.0;

  const float _thresholdFixedUpdateSteps = 15.0f;

  float _fixedTimeThreshold =
      this->_fixedUpdateTime * _thresholdFixedUpdateSteps;
  float _deltaTimeThreshold = 2.0f;

 public:
  MainLoopImpl(Ref<EngineEndStateStack> stateStack,
               Ref<EngineEndEventProvider> eventProvider,
               Ref<FactoryContainer> factoryContainer);
  ~MainLoopImpl() override;

#pragma region EngineEndMainLoop

  void tick() override;
  void run() override;

#pragma endregion

#pragma region MainLoop

  void setFixedUpdateTime(float fixedUpdateTime) noexcept override;

  [[nodiscard]] float getDeltaTime() const noexcept override;
  [[nodiscard]] float getFixedUpdateTime() const noexcept override;
  [[nodiscard]] double getSecondsSinceStart() const noexcept override;
  [[nodiscard]] std::size_t getTicksSinceStart() const noexcept override;
  [[nodiscard]] std::size_t getFixedUpdateTicks() const noexcept override;
#pragma endregion
};

}  // namespace vanadium
