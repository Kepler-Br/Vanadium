#ifndef VANADIUM_POPSTATECOMMAND_H
#define VANADIUM_POPSTATECOMMAND_H

#include "../core/Command.h"

namespace Vanadium
{
class Application;

class PopStateCommand: public Command
{
private:
    Application *app;

public:
    explicit PopStateCommand(Application *app):
            app(app)
    {}
    void execute() override
    {}
};

}


#endif //VANADIUM_POPSTATECOMMAND_H
