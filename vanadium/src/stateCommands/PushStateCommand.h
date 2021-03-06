#ifndef VANADIUM_PUSHSTATECOMMAND_H
#define VANADIUM_PUSHSTATECOMMAND_H

#include "core/interfaces/Command.h"
#include <string>

namespace Vanadium
{

class StateStack;
class State;
namespace StateStackCommands
{

class Push : public Command
{
private:
    StateStack *stateStack;
    State *state;
    const std::string &name;

public:
    Push(StateStack *stateStack, State *state, const std::string &name) :
            stateStack(stateStack),
            state(state),
            name(name)
    {}

    void execute() override;
};

}
}


#endif //VANADIUM_PUSHSTATECOMMAND_H
