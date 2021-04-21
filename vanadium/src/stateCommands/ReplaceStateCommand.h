#ifndef VANADIUM_REPLACESTATECOMMAND_H
#define VANADIUM_REPLACESTATECOMMAND_H

#include <string>

#include "core/interfaces/Command.h"

namespace Vanadium {

class StateStack;
class Application;
class State;
namespace StateStackCommands {

class Replace : public Command {
 private:
  StateStack *stateStack;
  Application *app;
  State *state;
  const std::string &name;

 public:
  Replace(StateStack *stateStack, Application *app, State *state,
          const std::string &name)
      : stateStack(stateStack), app(app), state(state), name(name) {}

  void execute() override;
};

}  // namespace StateStackCommands

}  // namespace Vanadium

#endif  // VANADIUM_REPLACESTATECOMMAND_H
