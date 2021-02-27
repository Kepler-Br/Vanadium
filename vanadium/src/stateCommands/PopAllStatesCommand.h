#ifndef VANADIUM_POPALLSTATESCOMMAND_H
#define VANADIUM_POPALLSTATESCOMMAND_H

#include "core/interfaces/Command.h"

namespace Vanadium
{
class StateStack;

namespace StateStackCommands
{

class PopAll: public Command
{
private:
    StateStack *stateStack;

public:
    explicit PopAll(StateStack *stateStack):
            stateStack(stateStack)
    {}
    void execute() override;
};

}

}

#endif //VANADIUM_POPALLSTATESCOMMAND_H
