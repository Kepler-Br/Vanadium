#pragma once

#include <vector>

#include "core/Types.h"
#include "core/interfaces/Command.h"
#include "core/interfaces/State.h"
#include "core/interfaces/StateStack.h"

namespace vanadium {

class EngineEndApplication;
class EventProvider;

class StateStackImpl : public EngineEndStateStack {
 private:
  WeakRef<EngineEndApplication> _application;
  Ref<EventProvider> _eventProvider;
  std::vector<Ref<State>> _states;
  std::vector<Ref<Command>> _commands;

 public:
  explicit StateStackImpl(WeakRef<EngineEndApplication> application,
                          Ref<EventProvider> eventProvider);

  ~StateStackImpl() override;

#pragma region EngineEndStateStack

  void push(Ref<State> state) override;
  void pop() override;
  void popAll() override;

  void executeCommands() override;

#pragma endregion

#pragma region StateStack

  [[nodiscard]] Ref<State> top() const noexcept override;
  [[nodiscard]] Ref<State> get(size_t index) const noexcept override;
  [[nodiscard]] size_t size() const noexcept override;
  [[nodiscard]] bool empty() const noexcept override;

  void requestPush(Ref<State> state) noexcept override;
  void requestPop() noexcept override;
  void requestPopAll() noexcept override;

  std::vector<Ref<State>>::iterator begin() override;
  std::vector<Ref<State>>::iterator end() override;
  std::vector<Ref<State>>::reverse_iterator rbegin() override;
  std::vector<Ref<State>>::reverse_iterator rend() override;

  [[nodiscard]] std::vector<Ref<State>>::const_iterator begin() const override;
  [[nodiscard]] std::vector<Ref<State>>::const_iterator end() const override;
  [[nodiscard]] std::vector<Ref<State>>::const_reverse_iterator rbegin()
      const override;
  [[nodiscard]] std::vector<Ref<State>>::const_reverse_iterator rend()
      const override;

#pragma endregion
};

}  // namespace vanadium
