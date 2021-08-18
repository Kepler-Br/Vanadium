#include "PopAllStatesCommand.h"

#include "core/application/StateStack.h"

namespace vanadium::state_stack_commands {

void PopAll::execute() { this->_stateStack->popAll(); }

}  // namespace vanadium::state_stack_commands