#pragma once

#include "vanadium/core/interfaces/Command.h"

namespace vanadium {
class EngineEndStateStack;
}

namespace vanadium::state_stack_commands {

class Pop : public Command {
 private:
  EngineEndStateStack *_stateStack;

 public:
  explicit Pop(EngineEndStateStack *stateStack);

  void execute() override;
};

}  // namespace vanadium::state_stack_commands
