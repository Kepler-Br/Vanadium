#ifndef VANADIUM_POPALLSTATESCOMMAND_H
#define VANADIUM_POPALLSTATESCOMMAND_H

#include "../core/Command.h"

namespace Van
{
class Application;

class PopAllStatesCommand: public Command
{
private:
    Application *app;

public:
    explicit PopAllStatesCommand(Application *app):
        app(app)
    {}
    void execute() override
    {}
};

}

#endif //VANADIUM_POPALLSTATESCOMMAND_H
