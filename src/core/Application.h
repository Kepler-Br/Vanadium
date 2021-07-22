#ifndef VANADIUM_APPLICATION_H
#define VANADIUM_APPLICATION_H

#include <glm/vec2.hpp>
#include <string>

#include "EventProvider.h"
#include "StateStack.h"
#include "Stopwatch.h"
#include "Types.h"
#include "Window.h"

namespace vanadium {

class StateEndApplication {
 public:
  [[nodiscard]] virtual double getDeltatime() const noexcept = 0;
  [[nodiscard]] virtual double getFixedUpdateTime() const noexcept = 0;
  [[nodiscard]] virtual double getSecondsSinceStart() const noexcept = 0;
  [[nodiscard]] virtual UserEndEventProvider *getEventProvider()
      const noexcept = 0;
  [[nodiscard]] virtual Window *getWindow() const noexcept = 0;
  [[nodiscard]] virtual size_t getTicksSinceStart() const noexcept = 0;
  [[nodiscard]] virtual size_t getFixedUpdateTicks() const noexcept = 0;
  [[nodiscard]] virtual UserEndStateStack *getStateStack() const noexcept = 0;
  virtual void stop() noexcept = 0;
  [[nodiscard]] virtual const std::vector<std::string> &getProgramArguments()
      const noexcept = 0;
};

class ApplicationProperties {
 private:
  WindowProperties windowProperties;
  std::vector<std::string> programArguments;

  void convertArguments(int argc, char **argv) {
    if (argv != nullptr) {
      this->programArguments.reserve((unsigned long)(argc));
      for (int i = 0; i < argc; i++) {
        this->programArguments.emplace_back(argv[i]);
      }
    }
  }

 public:
  ApplicationProperties(WindowProperties &winProps, int argc, char **argv)
      : windowProperties(winProps) {
    this->convertArguments(argc, argv);
  }

  WindowProperties getWindowProperties() const {
    return this->windowProperties;
  }

  std::vector<std::string> getArguments() const {
    return this->programArguments;
  }
};

class Application : public StateEndApplication {
 protected:
  EventProvider *eventProvider = nullptr;
  StateStack *stateStack = nullptr;
  Stopwatch *frameTime = nullptr;
  Window *window = nullptr;

  std::vector<std::string> programArguments;

  size_t ticksSinceStart = 0;
  size_t fixedUpdateTicks = 0;
  double deltatime = 1.0;
  const double fixedUpdateTime = 1.0 / 60.0;
  double timeSinceLastFixedUpdate = 0.0;
  double secondsSinceStart = 0.0;
  bool initializationInterrupted = false;

  void initVfs();

  virtual void tick();

 public:
  Application();
  virtual ~Application();

  void run();
  void stop() noexcept override;
  void init(const ApplicationProperties &properties);

  double getDeltatime() const noexcept override;
  double getFixedUpdateTime() const noexcept override;
  double getSecondsSinceStart() const noexcept override;
  size_t getTicksSinceStart() const noexcept override;
  size_t getFixedUpdateTicks() const noexcept override;
  Window *getWindow() const noexcept override;
  UserEndEventProvider *getEventProvider() const noexcept override;
  UserEndStateStack *getStateStack() const noexcept override;
  const std::vector<std::string> &getProgramArguments() const noexcept override;
  virtual void preInit() {}
  virtual void postInit() {}

  template <class T, typename... Args>
  void pushState(const std::string &name, Args &&..._args) {
    if (this->initializationInterrupted) {
      return;
    }
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
