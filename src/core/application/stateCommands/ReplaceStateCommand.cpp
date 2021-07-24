#include "ReplaceStateCommand.h"

#include "core/application/Application.h"
#include "core/application/State.h"

namespace vanadium::state_stack_commands {

void Replace::execute() {
  this->_stateStack->pop();
  this->_stateStack->push(this->_state, this->_name);
}

}  // namespace vanadium::state_stack_commands
