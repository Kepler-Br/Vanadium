#ifndef VANADIUM_POPSTATECOMMAND_H
#define VANADIUM_POPSTATECOMMAND_H

#include "../core/Command.h"

namespace Vanadium
{
class StateStack;

class PopStateCommand: public Command
{
private:
    StateStack *stateStack;

public:
    explicit PopStateCommand(StateStack *stateStack):
            stateStack(stateStack)
    {}
    void execute() override
    {}
};

}


#endif //VANADIUM_POPSTATECOMMAND_H
