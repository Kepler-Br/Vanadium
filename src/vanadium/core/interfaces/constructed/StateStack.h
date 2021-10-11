#pragma once

#include <vector>

#include "vanadium/core/types/Reference.h"

namespace vanadium {

class State;
class Application;

class StateStack {
 public:
  virtual ~StateStack() = default;

  [[nodiscard]] virtual Ref<State> top() const noexcept = 0;
  [[nodiscard]] virtual Ref<State> get(size_t index) const noexcept = 0;
  [[nodiscard]] virtual size_t size() const noexcept = 0;
  [[nodiscard]] virtual bool empty() const noexcept = 0;

  virtual void requestPush(Ref<State> state) noexcept = 0;
  virtual void requestPop() noexcept = 0;
  virtual void requestPopAll() noexcept = 0;

  virtual std::vector<Ref<State>>::iterator begin() = 0;
  virtual std::vector<Ref<State>>::iterator end() = 0;
  virtual std::vector<Ref<State>>::reverse_iterator rbegin() = 0;
  virtual std::vector<Ref<State>>::reverse_iterator rend() = 0;

  [[nodiscard]] virtual std::vector<Ref<State>>::const_iterator begin()
      const = 0;
  [[nodiscard]] virtual std::vector<Ref<State>>::const_iterator end() const = 0;
  [[nodiscard]] virtual std::vector<Ref<State>>::const_reverse_iterator rbegin()
      const = 0;
  [[nodiscard]] virtual std::vector<Ref<State>>::const_reverse_iterator rend()
      const = 0;
};

class EngineEndStateStack : public StateStack {
 public:
  ~EngineEndStateStack() override = default;

  virtual void setApplication(Application *application) = 0;
  virtual void push(Ref<State> state) = 0;
  virtual void pop() = 0;
  virtual void popAll() = 0;

  virtual void executeCommands() = 0;
};

}  // namespace vanadium
