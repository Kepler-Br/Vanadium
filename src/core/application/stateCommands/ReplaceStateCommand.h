#pragma once

#include <string>

#include "core/interfaces/Command.h"

namespace vanadium {

class StateStack;
class Application;
class State;

namespace state_stack_commands {

class Replace : public Command {
 private:
  StateStack *_stateStack;
  Application *_app;
  State *_state;
  const std::string &_name;

 public:
  Replace(StateStack *stateStack, Application *app, State *state,
          const std::string &name)
      : _stateStack(stateStack), _app(app), _state(state), _name(name) {}

  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium
