#include "PopStateCommand.h"

#include "core/application/StateStack.h"

namespace vanadium {

namespace state_stack_commands {

void Pop::execute() { this->_stateStack->pop(); }

}  // namespace state_stack_commands

}  // namespace vanadium