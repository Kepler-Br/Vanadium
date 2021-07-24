#include "PushStateCommand.h"

#include "core/application/StateStack.h"

namespace vanadium {

namespace state_stack_commands {

void Push::execute() { this->_stateStack->push(this->_state, this->_name); }

}  // namespace state_stack_commands

}  // namespace vanadium