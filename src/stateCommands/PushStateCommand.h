#ifndef VANADIUM_PUSHSTATECOMMAND_H
#define VANADIUM_PUSHSTATECOMMAND_H

#include "../core/Command.h"

namespace Vanadium
{
class Application;
class State;

class PushStateCommand: public Command
{
private:
    Application *app;
    State *state;

public:
    PushStateCommand(Application *app, State *state):
            app(app),
            state(state)
    {}
    void execute() override
    {}
};

}


#endif //VANADIUM_PUSHSTATECOMMAND_H
