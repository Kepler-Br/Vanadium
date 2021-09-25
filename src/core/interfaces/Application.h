#pragma once

#include <string>
#include <vector>

#include "core/interfaces/ApplicationInitHook.h"
#include "core/interfaces/EventProvider.h"
#include "core/interfaces/FactoryContainer.h"
#include "core/interfaces/MainLoop.h"
#include "core/interfaces/StateStack.h"
#include "core/interfaces/Subsystem.h"
#include "core/interfaces/constructed/Window.h"
#include "core/types/Reference.h"
#include "core/types/application/ApplicationProperties.h"

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
};

}  // namespace vanadium
