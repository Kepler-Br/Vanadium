#include "ReplaceStateCommand.h"

#include "../core/Application.h"
#include "../core/State.h"

namespace Vanadium {

namespace StateStackCommands {

void Replace::execute() {
  this->stateStack->pop();
  this->stateStack->push(this->state, this->name);
}

}  // namespace StateStackCommands

}  // namespace Vanadium