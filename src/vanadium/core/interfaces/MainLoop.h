#pragma once

#include <cstdlib>

#include "vanadium/core/types/Reference.h"

namespace vanadium {

class Application;
class StateStack;
class EventProvider;
class EngineEndApplication;
class EngineEndStateStack;

class MainLoop {
 public:
  virtual ~MainLoop() = default;

  virtual void setFixedUpdateTime(float fixedUpdateTime) noexcept = 0;

  [[nodiscard]] virtual float getDeltaTime() const noexcept = 0;
  [[nodiscard]] virtual float getFixedUpdateTime() const noexcept = 0;
  [[nodiscard]] virtual double getSecondsSinceStart() const noexcept = 0;
  [[nodiscard]] virtual std::size_t getTicksSinceStart() const noexcept = 0;
  [[nodiscard]] virtual std::size_t getFixedUpdateTicks() const noexcept = 0;
};

class EngineEndMainLoop : public MainLoop {
 public:
  ~EngineEndMainLoop() override = default;

  virtual void tick() = 0;

  virtual void run() = 0;
};

}  // namespace vanadium
