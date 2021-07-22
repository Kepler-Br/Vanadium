#include "PopStateCommand.h"

#include "core/StateStack.h"

namespace vanadium {

namespace state_stack_commands {

void Pop::execute() { this->stateStack->pop(); }

}  // namespace StateStackCommands

}  // namespace Vanadium