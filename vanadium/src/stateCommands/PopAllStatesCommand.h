#ifndef VANADIUM_POPALLSTATESCOMMAND_H
#define VANADIUM_POPALLSTATESCOMMAND_H

#include "../core/Command.h"

namespace Vanadium
{
class StateStack;

class PopAllStatesCommand: public Command
{
private:
    StateStack *stateStack;

public:
    explicit PopAllStatesCommand(StateStack *stateStack):
            stateStack(stateStack)
    {}
    void execute() override
    {}
};

}

#endif //VANADIUM_POPALLSTATESCOMMAND_H
