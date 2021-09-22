#pragma once

#include "core/Types.h"
#include "core/interfaces/Command.h"

namespace vanadium {

class EngineEndStateStack;
class State;

namespace state_stack_commands {

class Push : public Command {
 private:
  EngineEndStateStack *_stateStack;
  Ref<State> _state;

 public:
  Push(EngineEndStateStack *stateStack, Ref<State> state);

  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium
