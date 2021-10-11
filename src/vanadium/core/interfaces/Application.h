#pragma once

#include <string>
#include <vector>

#include "vanadium/core/interfaces/ApplicationInitHook.h"
#include "vanadium/core/interfaces/FactoryContainer.h"
#include "vanadium/core/interfaces/MainLoop.h"
#include "vanadium/core/interfaces/Subsystem.h"
#include "vanadium/core/interfaces/constructed/EventProvider.h"
#include "vanadium/core/interfaces/constructed/StateStack.h"
#include "vanadium/core/interfaces/constructed/Window.h"
#include "vanadium/core/types/Reference.h"
#include "vanadium/core/types/application/ApplicationProperties.h"

namespace vanadium {

class Application {
 public:
  virtual ~Application() = default;

  [[nodiscard]] virtual Ref<EventProvider> getEventProvider() noexcept = 0;
  [[nodiscard]] virtual Ref<Window> getWindow() noexcept = 0;
  [[nodiscard]] virtual Ref<StateStack> getStateStack() noexcept = 0;
  [[nodiscard]] virtual Ref<MainLoop> getMainLoop() noexcept = 0;
  [[nodiscard]] virtual Ref<FactoryContainer>
  getFactoryContainer() noexcept = 0;
  [[nodiscard]] virtual const ApplicationProperties &getProperties()
      const noexcept = 0;
  [[nodiscard]] virtual Ref<Subsystem> getSubsystem(
      const std::string &name) = 0;
  virtual void stop() = 0;
};

class EngineEndApplication : public Application {
 public:
  ~EngineEndApplication() override = default;

  virtual void run() = 0;
  virtual void setProperties(const ApplicationProperties &properties) = 0;
  virtual void setInitializationHook(Ref<ApplicationInitHook> initHook) = 0;
  virtual void addSubsystem(Ref<Subsystem> subsystem) = 0;
  virtual void initialize() = 0;

  [[nodiscard]] virtual Ref<EngineEndStateStack> getEngineStateStack() noexcept = 0;
  [[nodiscard]] virtual Ref<EngineEndMainLoop> getEngineMainLoop() noexcept = 0;
  [[nodiscard]] virtual Ref<EngineEndEventProvider> getEngineEventProvider() noexcept = 0;

  virtual void pushState(Ref<State> state) = 0;

  template <class TSubsystem, class... Args>
  void addSubsystem(Args &&...args) {
    Ref<Subsystem> subsystem = MakeRef<TSubsystem>(std::forward<Args>(args)...);

    this->addSubsystem(subsystem);
  }

  template <class TState, class... Args>
  void pushState(Args &&...args) {
    Ref<State> state = MakeRef<TState>(std::forward<Args>(args)...);

    this->pushState(state);
  }
};

}  // namespace vanadium
