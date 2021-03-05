#ifndef VANADIUM_SVG_PATH_H
#define VANADIUM_SVG_PATH_H

#include <string>
#include <utility>
#include <vector>

#include "Commands.h"

namespace Vanadium
{

namespace Svg
{

class Path
{
private:
    std::vector<Commands::Command *> commands;

public:
    Path(const std::initializer_list<Commands::Command *> &list) :
        commands(list)
    {}

    Path(std::vector<Commands::Command *> commands) :
            commands(std::move(commands))
    {}

    ~Path()
    {
        for (Commands::Command *command : this->commands)
        {
            delete command;
        }
        this->commands.clear();
    }

    [[nodiscard]]
    const std::vector<Commands::Command *> &getCommands() const noexcept
    {
        return this->commands;
    }

};

}

}

#endif //VANADIUM_SVG_PATH_H
