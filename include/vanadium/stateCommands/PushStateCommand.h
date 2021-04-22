#ifndef VANADIUM_PUSHSTATECOMMAND_H
#define VANADIUM_PUSHSTATECOMMAND_H

#include <string>

#include "core/interfaces/Command.h"

namespace Vanadium {

class StateStack;
class State;
namespace StateStackCommands {

class Push : public Command {
 private:
  StateStack *stateStack;
  State *state;
  const std::string &name;

 public:
  Push(StateStack *stateStack, State *state, const std::string &name)
      : stateStack(stateStack), state(state), name(name) {}

  void execute() override;
};

}  // namespace StateStackCommands
}  // namespace Vanadium

#endif  // VANADIUM_PUSHSTATECOMMAND_H
