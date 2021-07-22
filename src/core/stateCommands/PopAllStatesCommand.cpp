#include "PopAllStatesCommand.h"

#include "core/StateStack.h"

namespace vanadium {

namespace state_stack_commands {

void PopAll::execute() { this->stateStack->popAll(); }

}  // namespace state_stack_commands

}  // namespace vanadium