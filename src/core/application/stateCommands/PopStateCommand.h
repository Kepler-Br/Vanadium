#pragma once

#include "core/Types.h"
#include "core/interfaces/Command.h"

namespace vanadium {

class EngineEndStateStack;

namespace state_stack_commands {

class Pop : public Command {
 private:
  EngineEndStateStack *_stateStack;

 public:
  explicit Pop(EngineEndStateStack *stateStack);

  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium
