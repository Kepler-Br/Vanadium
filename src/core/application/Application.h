#pragma once

#include <glm/vec2.hpp>
#include <string>
#include <utility>

#include "ApplicationProperties.h"
#include "StateStack.h"
#include "core/EventProvider.h"
#include "core/Stopwatch.h"
#include "core/Types.h"
#include "core/Window.h"
#include "core/interfaces/Subsystem.h"

namespace vanadium {

class EngineEndMainLoop;

class UserEndApplication {
 public:
  virtual ~UserEndApplication() = default;

  virtual void setFixedUpdateTime(double newFixedUpdateTime) noexcept = 0;

  [[nodiscard]] virtual Ref<UserEndEventProvider> getEventProvider()
      const noexcept = 0;
  [[nodiscard]] virtual Ref<Window> getWindow() const noexcept = 0;
  [[nodiscard]] virtual Ref<UserEndStateStack> getStateStack()
      const noexcept = 0;
  virtual void stop() noexcept = 0;
  [[nodiscard]] virtual const std::vector<std::string> &getProgramArguments()
      const noexcept = 0;
};

class Application : public UserEndApplication {
 protected:
  Ref<EventProvider> _eventProvider = nullptr;
  Ref<StateStack> _stateStack = nullptr;
  Ref<Window> _window = nullptr;
  Ref<EngineEndMainLoop> _mainLoop = nullptr;
  std::vector<Ref<Subsystem>> _subsystems;

  std::vector<std::string> _programArguments;

  bool _initializationInterrupted = false;

 public:
  Application();
  ~Application() override;

  void initialize(Ref<EngineEndMainLoop> mainLoop, Ref<StateStack> stateStack, Ref<EventProvider> eventProvider);

  void run();
  void setProperties(const ApplicationProperties &properties);

  [[nodiscard]] Ref<Window> getWindow() const noexcept override;
  [[nodiscard]] Ref<UserEndEventProvider> getEventProvider()
      const noexcept override;
  [[nodiscard]] Ref<UserEndStateStack> getStateStack() const noexcept override;
  [[nodiscard]] const std::vector<std::string> &getProgramArguments()
      const noexcept override;

  virtual void preInit() {
    // noop.
  }
  virtual void postInit() {
    // noop.
  }

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
