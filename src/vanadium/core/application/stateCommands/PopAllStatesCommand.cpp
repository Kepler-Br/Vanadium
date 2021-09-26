#include "PopAllStatesCommand.h"

#include "vanadium/core/interfaces/StateStack.h"

namespace vanadium::state_stack_commands {

PopAll::PopAll(EngineEndStateStack *stateStack) : _stateStack(stateStack) {}

void PopAll::execute() { this->_stateStack->popAll(); }

}  // namespace vanadium::state_stack_commands
