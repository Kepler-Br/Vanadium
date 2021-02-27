#include "ReplaceStateCommand.h"
#include "../core/State.h"
#include "../core/Application.h"

namespace Vanadium
{

namespace StateStackCommands
{

void Replace::execute()
{
    this->stateStack->pop();
    this->stateStack->push(this->state, this->name);
}

}

}