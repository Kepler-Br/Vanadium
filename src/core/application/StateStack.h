#ifndef VANADIUM_APPLICATION_STATESTACK_H
#define VANADIUM_APPLICATION_STATESTACK_H

#include <vector>

#include "core/Types.h"
#include "core/application/State.h"
#include "core/interfaces/Command.h"

namespace vanadium {

class UserEndApplication;

class UserEndStateStack {
 protected:
  std::vector<State *> _states;

 public:
  [[nodiscard]] virtual State *top() const noexcept = 0;
  [[nodiscard]] virtual State *get(size_t index) const noexcept = 0;
  [[nodiscard]] virtual size_t size() const noexcept = 0;
  virtual void requestPush(State *state, const std::string &name) noexcept = 0;
  virtual void requestPop() noexcept = 0;
  virtual void requestPopAll() noexcept = 0;

  std::vector<State *>::iterator begin() { return _states.begin(); }
  std::vector<State *>::iterator end() { return _states.end(); }
  std::vector<State *>::reverse_iterator rbegin() { return _states.rbegin(); }
  std::vector<State *>::reverse_iterator rend() { return _states.rend(); }

  [[nodiscard]] std::vector<State *>::const_iterator begin() const {
    return _states.begin();
  }
  [[nodiscard]] std::vector<State *>::const_iterator end() const {
    return _states.end();
  }
  [[nodiscard]] std::vector<State *>::const_reverse_iterator rbegin() const {
    return _states.rbegin();
  }
  [[nodiscard]] std::vector<State *>::const_reverse_iterator rend() const {
    return _states.rend();
  }
};

class StateStack : public UserEndStateStack {
 private:
  UserEndApplication *_application;
  std::vector<Command *> _commands;

 public:
  explicit StateStack(UserEndApplication *application);
  ~StateStack();

  [[nodiscard]] State *top() const noexcept override;
  [[nodiscard]] State *get(size_t index) const noexcept override;
  [[nodiscard]] size_t size() const noexcept override;
  void requestPush(State *state, const std::string &name) noexcept override;
  void requestPop() noexcept override;
  void requestPopAll() noexcept override;

  void push(State *state, const std::string &name);
  void pop();
  void popAll();

  void executeCommands();
};

}  // namespace vanadium

#endif  // VANADIUM_APPLICATION_STATESTACK_H
