#pragma once

#include "core/interfaces/Command.h"

namespace vanadium {

class StateStack;

namespace state_stack_commands {

class PopAll : public Command {
 private:
  StateStack *_stateStack;

 public:
  explicit PopAll(StateStack *stateStack) : _stateStack(stateStack) {}
  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium
