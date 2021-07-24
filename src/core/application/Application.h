#ifndef VANADIUM_APPLICATION_H
#define VANADIUM_APPLICATION_H

#include <glm/vec2.hpp>
#include <string>

#include "StateStack.h"
#include "core/EventProvider.h"
#include "core/Stopwatch.h"
#include "core/Types.h"
#include "core/Window.h"
#include "graphics/BgfxContext.h"

namespace vanadium {

class UserEndApplication {
 public:
  virtual void setFixedUpdateTime(double newFixedUpdateTime) noexcept = 0;

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
  WindowProperties _windowProperties;
  std::vector<std::string> _programArguments;

  void convertArguments(int argc, char **argv) {
    if (argv != nullptr) {
      this->_programArguments.reserve((size_t)argc);
      for (int i = 0; i < argc; i++) {
        this->_programArguments.emplace_back(argv[i]);
      }
    }
  }

 public:
  ApplicationProperties(WindowProperties &winProps, int argc, char **argv)
      : _windowProperties(winProps) {
    this->convertArguments(argc, argv);
  }

  [[nodiscard]] const WindowProperties &getWindowProperties() const {
    return this->_windowProperties;
  }

  [[nodiscard]] const std::vector<std::string> &getArguments() const {
    return this->_programArguments;
  }
};

class Application : public UserEndApplication {
 protected:
  EventProvider *_eventProvider = nullptr;
  StateStack *_stateStack = nullptr;
  Stopwatch *_frameTime = nullptr;
  Window *_window = nullptr;
  BgfxContext *_bgfxContext = nullptr;

  std::vector<std::string> _programArguments;

  size_t _ticksSinceStart = 0;
  size_t _fixedUpdateTicks = 0;
  double _deltatime = 1.0;
  double _fixedUpdateTime = 1.0 / 60.0;
  double _timeSinceLastFixedUpdate = 0.0;
  double _secondsSinceStart = 0.0;
  bool _initializationInterrupted = false;

  void initVfs();

  virtual void tick();

 public:
  Application();
  virtual ~Application();

  void run();
  void stop() noexcept override;
  void init(const ApplicationProperties &properties);

  void setFixedUpdateTime(double newFixedUpdateTime) noexcept override;

  [[nodiscard]] double getDeltatime() const noexcept override;
  [[nodiscard]] double getFixedUpdateTime() const noexcept override;
  [[nodiscard]] double getSecondsSinceStart() const noexcept override;
  [[nodiscard]] size_t getTicksSinceStart() const noexcept override;
  [[nodiscard]] size_t getFixedUpdateTicks() const noexcept override;
  [[nodiscard]] Window *getWindow() const noexcept override;
  [[nodiscard]] UserEndEventProvider *getEventProvider()
      const noexcept override;
  [[nodiscard]] UserEndStateStack *getStateStack() const noexcept override;
  [[nodiscard]] const std::vector<std::string> &getProgramArguments()
      const noexcept override;
  virtual void preInit() {}
  virtual void postInit() {}

  template <class T, typename... Args>
  void pushState(const std::string &name, Args &&..._args) {
    if (this->_initializationInterrupted) {
      return;
    }
    try {
      this->_stateStack->push(new T(std::forward<Args>(_args)...), name);
    } catch (const std::runtime_error &e) {
      VAN_ENGINE_CRITICAL("Execution interrupted with message: {}", e.what());
      this->_stateStack->popAll();
    }
  }
};

}  // namespace vanadium
#endif  // VANADIUM_APPLICATION_H
