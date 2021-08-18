#pragma once

#include <string>
#include <utility>

#include "core/interfaces/Command.h"

namespace vanadium {

class StateStack;
class Application;
class State;

namespace state_stack_commands {

class Replace : public Command {
 private:
  StateStack *_stateStack;
  State *_state;
  const std::string _name;

 public:
  Replace(StateStack *stateStack, State *state,
          std::string name)
      : _stateStack(stateStack), _state(state), _name(std::move(name)) {}

  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium
