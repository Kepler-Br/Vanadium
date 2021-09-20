#pragma once

#include "core/interfaces/MainLoop.h"

namespace vanadium {

class Application;
class StateStack;
class EventProvider;
class Stopwatch;

class ApplicationMainLoop : public MainLoop {
 private:
  Ref<Stopwatch> _frameTime = nullptr;

  Ref<StateStack> _stateStack = nullptr;
  Ref<Application> _application = nullptr;
  Ref<EventProvider> _eventProvider = nullptr;

  size_t _ticksSinceStart = 0;
  size_t _fixedUpdateTicks = 0;
  float _deltatime = 1.0f;
  float _fixedUpdateTime = 1.0f / 60.0f;
  double _secondsSinceStart = 0.0;

  float _timeSinceLastFixedUpdate = 0.0;

 public:
  ApplicationMainLoop();

  ~ApplicationMainLoop() override = default;

  void initialize(Ref<Application> application, Ref<StateStack> stateStack,
                  Ref<EventProvider> _eventProvider) override;

  void deinitialize() override;

  void tick() override;
  void run() override;

  void setFixedUpdateTime(float fixedUpdateTime) noexcept override;

  [[nodiscard]] float getDeltatime() const noexcept override;
  [[nodiscard]] float getFixedUpdateTime() const noexcept override;
  [[nodiscard]] double getSecondsSinceStart() const noexcept override;
  [[nodiscard]] std::size_t getTicksSinceStart() const noexcept override;
  [[nodiscard]] std::size_t getFixedUpdateTicks() const noexcept override;

  Ref<Application> getApplication() override;
  Ref<StateStack> getStateStack() override;
  Ref<EventProvider> getEventProvider() override;
};

}  // namespace vanadium
