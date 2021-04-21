#include "PopStateCommand.h"

#include "../core/StateStack.h"

namespace Vanadium {

namespace StateStackCommands {

void Pop::execute() { this->stateStack->pop(); }

}  // namespace StateStackCommands

}  // namespace Vanadium