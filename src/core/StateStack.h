#ifndef VANADIUM_STATESTACK_H
#define VANADIUM_STATESTACK_H

#include <vector>

#include "State.h"
#include "Types.h"
#include "interfaces/Command.h"

namespace vanadium {

class UserEndApplication;

class UserEndStateStack {
 protected:
  std::vector<State *> states;

 public:
  [[nodiscard]] virtual State *top() const noexcept = 0;
  [[nodiscard]] virtual State *get(size_t index) const noexcept = 0;
  [[nodiscard]] virtual size_t size() const noexcept = 0;
  virtual void requestPush(State *state, const std::string &name) noexcept = 0;
  virtual void requestPop() noexcept = 0;
  virtual void requestPopAll() noexcept = 0;

  std::vector<State *>::iterator begin() { return states.begin(); }
  std::vector<State *>::iterator end() { return states.end(); }
  std::vector<State *>::reverse_iterator rbegin() { return states.rbegin(); }
  std::vector<State *>::reverse_iterator rend() { return states.rend(); }

  [[nodiscard]] std::vector<State *>::const_iterator begin() const {
    return states.begin();
  }
  [[nodiscard]] std::vector<State *>::const_iterator end() const {
    return states.end();
  }
  [[nodiscard]] std::vector<State *>::const_reverse_iterator rbegin() const {
    return states.rbegin();
  }
  [[nodiscard]] std::vector<State *>::const_reverse_iterator rend() const {
    return states.rend();
  }
};

class StateStack : public UserEndStateStack {
 private:
  UserEndApplication *application;
  std::vector<Command *> commands;

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

}  // namespace Vanadium

#endif  // VANADIUM_STATESTACK_H
