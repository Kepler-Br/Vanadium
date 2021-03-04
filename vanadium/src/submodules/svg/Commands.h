#ifndef VANADIUM_SVG_COMMANDS_H
#define VANADIUM_SVG_COMMANDS_H

#include <glm/vec2.hpp>

#include "Parser.h"
#include "Types.h"

namespace Vanadium
{

namespace Svg
{

namespace Commands
{

struct Command
{
public:
    virtual ~Command() = default;
    virtual Commands::Type getType() = 0;

};

struct Move : public Command
{
    Commands::CoordinateType coordinateType;
    const glm::vec2 moveTarget;

    Move(Commands::CoordinateType coordinateType, const glm::vec2 &target) :
        coordinateType(coordinateType),
        moveTarget(target)
    {}

    Commands::Type getType() override
    {
        return Commands::Type::Move;
    }
};

struct Cubic : public Command
{
    Commands::CoordinateType coordinateType;
    std::vector<glm::vec2> joints;

    Cubic(Commands::CoordinateType coordinateType,
          const std::initializer_list<glm::vec2> &initializerList) :
        coordinateType(coordinateType),
        joints(initializerList)
    {}

    Commands::Type getType() override
    {
        return Commands::Type::Cubic;
    }
};

struct Line : public Command
{
    Commands::CoordinateType coordinateType;
    glm::vec2 target;

    Line(Commands::CoordinateType coordinateType, const glm::vec2 &target) :
        coordinateType(coordinateType),
        target(target)
    {}

    Commands::Type getType() override
    {
        return Commands::Type::Line;
    }
};

}

}

}

#endif //VANADIUM_SVG_COMMANDS_H
