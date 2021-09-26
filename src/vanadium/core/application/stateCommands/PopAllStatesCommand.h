#pragma once

#include "vanadium/core/interfaces/Command.h"

namespace vanadium {
class EngineEndStateStack;
}

namespace vanadium::state_stack_commands {

class PopAll : public Command {
 private:
  EngineEndStateStack *_stateStack;

 public:
  explicit PopAll(EngineEndStateStack *stateStack);

  void execute() override;
};

}  // namespace vanadium::state_stack_commands
