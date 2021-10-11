#include "PopStateCommand.h"

#include "vanadium/core/interfaces/constructed/StateStack.h"

namespace vanadium::state_stack_commands {

Pop::Pop(EngineEndStateStack *stateStack) : _stateStack(stateStack) {}

void Pop::execute() { this->_stateStack->pop(); }

}  // namespace vanadium::state_stack_commands
