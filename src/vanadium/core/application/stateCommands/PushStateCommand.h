#pragma once

#include "vanadium/core/interfaces/Command.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {
class EngineEndStateStack;
class State;
}  // namespace vanadium

namespace vanadium::state_stack_commands {

class Push : public Command {
 private:
  EngineEndStateStack *_stateStack;
  Ref<State> _state;

 public:
  Push(EngineEndStateStack *stateStack, Ref<State> state);

  void execute() override;
};

}  // namespace vanadium::state_stack_commands