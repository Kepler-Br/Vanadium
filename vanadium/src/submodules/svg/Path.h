#ifndef VANADIUM_SVG_PATH_H
#define VANADIUM_SVG_PATH_H

#include <string>
#include <utility>
#include <vector>

namespace Vanadium
{

namespace Svg
{

class Path
{
private:
    std::string name;
    std::vector<Commands::Command *> commands;

public:
    Path(std::string name, const std::initializer_list<Commands::Command *> &list) :
        name(std::move(name)),
        commands(list)
    {}

    Path(std::string name, std::vector<Commands::Command *> commands) :
            name(std::move(name)),
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

    [[nodiscard]]
    std::string getName() const noexcept
    {
        return name;
    }

};

}

}

#endif //VANADIUM_SVG_PATH_H
