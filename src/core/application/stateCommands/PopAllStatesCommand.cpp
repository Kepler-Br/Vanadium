#include "PopAllStatesCommand.h"

#include "core/application/StateStack.h"

namespace vanadium {

namespace state_stack_commands {

void PopAll::execute() { this->_stateStack->popAll(); }

}  // namespace state_stack_commands

}  // namespace vanadium