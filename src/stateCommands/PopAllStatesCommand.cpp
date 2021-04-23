#include "stateCommands/PopAllStatesCommand.h"

#include "core/StateStack.h"

namespace Vanadium {

namespace StateStackCommands {

void PopAll::execute() { this->stateStack->popAll(); }

}  // namespace StateStackCommands

}  // namespace Vanadium