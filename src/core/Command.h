#ifndef VANADIUM_COMMAND_H
#define VANADIUM_COMMAND_H

namespace Van
{

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
    virtual void undo() {}
};

}

#endif //VANADIUM_COMMAND_H
