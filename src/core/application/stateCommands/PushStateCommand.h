#ifndef VANADIUM_APPLICATIONSTATECOMMANDS_PUSHSTATECOMMAND_H
#define VANADIUM_APPLICATIONSTATECOMMANDS_PUSHSTATECOMMAND_H

#include <string>

#include "core/interfaces/Command.h"

namespace vanadium {

class StateStack;
class State;

namespace state_stack_commands {

class Push : public Command {
 private:
  StateStack *_stateStack;
  State *_state;
  const std::string &_name;

 public:
  Push(StateStack *stateStack, State *state, const std::string &name)
      : _stateStack(stateStack), _state(state), _name(name) {}

  void execute() override;
};

}  // namespace state_stack_commands

}  // namespace vanadium

#endif  // VANADIUM_APPLICATIONSTATECOMMANDS_PUSHSTATECOMMAND_H
