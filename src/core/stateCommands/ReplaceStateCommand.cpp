#include "ReplaceStateCommand.h"

#include "core/Application.h"
#include "core/State.h"

namespace vanadium::state_stack_commands {

void Replace::execute() {
  this->stateStack->pop();
  this->stateStack->push(this->state, this->name);
}

}  // namespace vanadium::state_stack_commands
