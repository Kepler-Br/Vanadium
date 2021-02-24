#ifndef VANADIUM_PUSHSTATECOMMAND_H
#define VANADIUM_PUSHSTATECOMMAND_H

#include "../core/Command.h"
#include <string>

namespace Vanadium
{
class StateStack;
class State;

class PushStateCommand: public Command
{
private:
    StateStack *stateStack;
    State *state;

public:
    PushStateCommand(StateStack *stateStack, State *state, const std::string &name):
            stateStack(stateStack),
            state(state)
    {}
    void execute() override
    {}
};

}


#endif //VANADIUM_PUSHSTATECOMMAND_H
