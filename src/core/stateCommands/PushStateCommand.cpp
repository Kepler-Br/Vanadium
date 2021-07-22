#include "PushStateCommand.h"

#include "core/StateStack.h"

namespace vanadium {

namespace state_stack_commands {

void Push::execute() { this->stateStack->push(this->state, this->name); }

}  // namespace StateStackCommands

}  // namespace Vanadium