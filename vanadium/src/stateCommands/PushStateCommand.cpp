#include "PushStateCommand.h"
#include "../core/StateStack.h"

namespace Vanadium
{

namespace StateStackCommands
{

void Push::execute()
{
    this->stateStack->push(this->state, this->name);
}

}

}