#ifndef VANADIUM_POPSTATECOMMAND_H
#define VANADIUM_POPSTATECOMMAND_H

#include "core/interfaces/Command.h"

namespace vanadium {

class StateStack;
namespace state_stack_commands {

class Pop : public Command {
 private:
  StateStack *stateStack;

 public:
  explicit Pop(StateStack *stateStack) : stateStack(stateStack) {}

  void execute() override;
};

}  // namespace StateStackCommands

}  // namespace Vanadium

#endif  // VANADIUM_POPSTATECOMMAND_H
