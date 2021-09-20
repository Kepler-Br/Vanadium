#include "PopStateCommand.h"

#include "core/application/StateStack.h"

namespace vanadium::state_stack_commands {

void Pop::execute() { this->_stateStack->pop(); }

}  // namespace vanadium::state_stack_commands