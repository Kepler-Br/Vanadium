#pragma once

#include <vector>

#include "core/Types.h"
#include "core/application/State.h"
#include "core/interfaces/Command.h"
#include "core/interfaces/StateStack.h"

namespace vanadium {

class EngineEndApplication;

// class UserEndStateStack {
//  protected:
//   std::vector<State *> _states;
//
//  public:
//   virtual ~UserEndStateStack() = default;
//
//   [[nodiscard]] virtual State *top() const noexcept = 0;
//   [[nodiscard]] virtual State *get(size_t index) const noexcept = 0;
//   [[nodiscard]] virtual size_t size() const noexcept = 0;
//   [[nodiscard]] virtual bool empty() const noexcept = 0;
//
//   virtual void requestPush(State *state, const std::string &name) noexcept =
//   0; virtual void requestPop() noexcept = 0; virtual void requestPopAll()
//   noexcept = 0;
//
//   std::vector<State *>::iterator begin() { return _states.begin(); }
//   std::vector<State *>::iterator end() { return _states.end(); }
//   std::vector<State *>::reverse_iterator rbegin() { return _states.rbegin();
//   } std::vector<State *>::reverse_iterator rend() { return _states.rend(); }
//
//   [[nodiscard]] std::vector<State *>::const_iterator begin() const {
//     return _states.begin();
//   }
//   [[nodiscard]] std::vector<State *>::const_iterator end() const {
//     return _states.end();
//   }
//   [[nodiscard]] std::vector<State *>::const_reverse_iterator rbegin() const {
//     return _states.rbegin();
//   }
//   [[nodiscard]] std::vector<State *>::const_reverse_iterator rend() const {
//     return _states.rend();
//   }
// };

class StateStackImpl : public EngineEndStateStack {
 private:
  WeakRef<EngineEndApplication> _application;
  std::vector<Ref<State>> _states;
  std::vector<Ref<Command>> _commands;

 public:
  explicit StateStackImpl(WeakRef<EngineEndApplication> application);

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

  //  [[nodiscard]] State *top() const noexcept override;
  //  [[nodiscard]] State *get(size_t index) const noexcept override;
  //  [[nodiscard]] size_t size() const noexcept override;
  //  [[nodiscard]] bool empty() const noexcept override;
  //  void requestPush(State *state, const std::string &name) noexcept override;
  //  void requestPop() noexcept override;
  //  void requestPopAll() noexcept override;
  //
  //  void push(State *state, const std::string &name);
  //  void pop();
  //  void popAll();
  //
  //  void executeCommands();
};

}  // namespace vanadium
