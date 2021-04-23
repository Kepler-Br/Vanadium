#ifndef VANADIUM_APPLICATION_H
#define VANADIUM_APPLICATION_H

#include <glm/vec2.hpp>
#include <string>

#include "EventProvider.h"
#include "StateStack.h"
#include "Stopwatch.h"
#include "Types.h"
#include "Window.h"

namespace Vanadium {

class StateEndApplication {
 public:
  [[nodiscard]] virtual double getDeltatime() const noexcept = 0;
  [[nodiscard]] virtual double getFixedUpdateTime() const noexcept = 0;
  [[nodiscard]] virtual double getSecondsSinceStart() const noexcept = 0;
  [[nodiscard]] virtual UserEndEventProvider *getEventProvider()
      const noexcept = 0;
  [[nodiscard]] virtual Window *getWindow() const noexcept = 0;
  [[nodiscard]] virtual VNsize getTicksSinceStart() const noexcept = 0;
  [[nodiscard]] virtual VNsize getFixedUpdateTicks() const noexcept = 0;
  [[nodiscard]] virtual UserEndStateStack *getStateStack() const noexcept = 0;
  virtual void stop() noexcept = 0;
  [[nodiscard]] virtual const std::vector<std::string> &getProgramArguments()
      const noexcept = 0;
};

class Application : public StateEndApplication {
 public:
  struct Properties {
    Window::Properties winProps;
    int argc = 0;
    char **argv = nullptr;
  };

 protected:
  EventProvider *eventProvider = nullptr;
  StateStack *stateStack = nullptr;
  Stopwatch *frameTime = nullptr;
  Window *window = nullptr;

  std::vector<std::string> programArguments;

  VNsize ticksSinceStart = 0;
  VNsize fixedUpdateTicks = 0;
  double deltatime = 1.0;
  const double fixedUpdateTime = 1.0 / 60.0;
  double timeSinceLastFixedUpdate = 0.0;
  double secondsSinceStart = 0.0;
  bool initializationInterrupted = false;
  Application::Properties specs;

  virtual void tick();

 public:
  Application(const Application::Properties &specs);
  virtual ~Application();

  void run();
  void stop() noexcept override;
  void init();

  double getDeltatime() const noexcept override;
  double getFixedUpdateTime() const noexcept override;
  double getSecondsSinceStart() const noexcept override;
  VNsize getTicksSinceStart() const noexcept override;
  VNsize getFixedUpdateTicks() const noexcept override;
  Window *getWindow() const noexcept override;
  UserEndEventProvider *getEventProvider() const noexcept override;
  UserEndStateStack *getStateStack() const noexcept override;
  const std::vector<std::string> &getProgramArguments() const noexcept override;
  virtual void preInit() {}
  virtual void postInit() {}

  template <class T, typename... Args>
  void pushState(const std::string &name, Args &&..._args) {
    if (this->initializationInterrupted) return;
    try {
      this->stateStack->push(new T(std::forward<Args>(_args)...), name);
    } catch (const std::runtime_error &e) {
      VAN_ENGINE_CRITICAL("Execution interrupted with message: {}", e.what());
      this->stateStack->popAll();
    }
  }
};

}  // namespace Vanadium
#endif  // VANADIUM_APPLICATION_H
