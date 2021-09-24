#pragma once

#include <string>
#include <vector>

namespace vanadium {

class EngineEndMainLoop;
class MainLoop;
class Window;
class ApplicationProperties;
class EventProvider;
class StateStack;
class Subsystem;

class Application {
 public:
  virtual ~Application() = default;

  [[nodiscard]] virtual Ref<EventProvider> getEventProvider() noexcept = 0;
  [[nodiscard]] virtual Ref<Window> getWindow() noexcept = 0;
  [[nodiscard]] virtual Ref<StateStack> getStateStack() noexcept = 0;
  [[nodiscard]] virtual Ref<MainLoop> getMainLoop() noexcept = 0;
  virtual void stop() = 0;
  [[nodiscard]] virtual const ApplicationProperties &getProperties()
      const noexcept = 0;
  [[nodiscard]] virtual Ref<Subsystem> getSubsystem(
      const std::string &name) = 0;
};

class EngineEndApplication : public Application {
 public:
  ~EngineEndApplication() override = default;

  virtual void run() = 0;
  virtual void setProperties(const ApplicationProperties &properties) = 0;
  virtual void addSubsystem(Ref<Subsystem> subsystem) = 0;
  virtual void initializeSubsystems() = 0;
};

}  // namespace vanadium
