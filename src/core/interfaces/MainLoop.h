#pragma once

#include <cstdlib>

#include "core/Types.h"

namespace vanadium {

class Application;
class StateStackImpl;
class EventProvider;

class MainLoop {
 public:
  virtual ~MainLoop() = 0;

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

class EngineEndMainLoop : public MainLoop {
 public:
  ~EngineEndMainLoop() override = 0;

  virtual void initialize(Ref<Application> application,
                          Ref<StateStack> stateStack,
                          Ref<EventProvider> eventProvider) = 0;
  virtual void deinitialize() = 0;

  virtual void tick() = 0;

  virtual void run() = 0;
};

}  // namespace vanadium
