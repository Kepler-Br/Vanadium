#include "ReplaceStateCommand.h"

#include "core/application/Application.h"
#include "core/application/State.h"

namespace vanadium::state_stack_commands {

void Replace::execute() {
  this->stateStack->pop();
  this->stateStack->push(this->state, this->name);
}

}  // namespace vanadium::state_stack_commands
