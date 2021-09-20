#pragma once

#include <cstdlib>

#include "core/Types.h"

namespace vanadium {

class Application;
class StateStack;
class EventProvider;

class EngineEndMainLoop {
 public:
  virtual ~EngineEndMainLoop() = 0;

  virtual void initialize(Ref<Application> application,
                          Ref<StateStack> stateStack,
                          Ref<EventProvider> eventProvider) = 0;
  virtual void deinitialize() = 0;

  virtual void tick() = 0;

  virtual void run() = 0;
};

class MainLoop : public EngineEndMainLoop {
 public:
  ~MainLoop() override = 0;

  virtual void setFixedUpdateTime(float fixedUpdateTime) noexcept = 0;

  [[nodiscard]] virtual float getDeltatime() const noexcept = 0;
  [[nodiscard]] virtual float getFixedUpdateTime() const noexcept = 0;
  [[nodiscard]] virtual double getSecondsSinceStart() const noexcept = 0;
  [[nodiscard]] virtual std::size_t getTicksSinceStart() const noexcept = 0;
  [[nodiscard]] virtual std::size_t getFixedUpdateTicks() const noexcept = 0;

  virtual Ref<Application> getApplication() = 0;
  virtual Ref<StateStack> getStateStack() = 0;
  virtual Ref<EventProvider> getEventProvider() = 0;
};

}  // namespace vanadium
