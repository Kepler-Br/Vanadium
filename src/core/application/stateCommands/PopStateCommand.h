#pragma once

#include "core/interfaces/Command.h"

namespace vanadium {

class StateStack;

namespace state_stack_commands {

class Pop : public Command {
 private:
  StateStack *_stateStack;

 public:
  explicit Pop(StateStack *stateStack) : _stateStack(stateStack) {}

  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium
