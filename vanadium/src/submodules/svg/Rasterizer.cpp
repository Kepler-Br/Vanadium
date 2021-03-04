#include "../../core/Math.h"
#include "Rasterizer.h"
#include "Commands.h"
#include "Path.h"

#include <iostream>

namespace Vanadium
{

namespace Svg
{

glm::vec2 Rasterizer::rasterizeCubicStep(const glm::vec2 &previousPoint, const Commands::Cubic *command, VNfloat t)
{
    const glm::vec2 &p0 = previousPoint;
    const glm::vec2 &p1 = std::get<0>(command->points);
    const glm::vec2 &p2 = std::get<1>(command->points);
    const glm::vec2 &p3 = std::get<2>(command->points);

    glm::vec2 A = Math::lerp(p0, p1, t);
    glm::vec2 B = Math::lerp(p1, p2, t);
    glm::vec2 C = Math::lerp(p2, p3, t);
    glm::vec2 D = Math::lerp(A, B, t);
    glm::vec2 E = Math::lerp(B, C, t);
    glm::vec2 F = Math::lerp(D, E, t); // The juicy one

    return F;
}

std::vector<VNfloat> Rasterizer::rasterizeCubic(const glm::vec2 &previousPoint, const Commands::Cubic *command, VNuint quality)
{
    std::vector<VNfloat> vertices;

    vertices.reserve((2 + quality) * 2);

    vertices.emplace_back(previousPoint.x);
    vertices.emplace_back(previousPoint.y);

    for (VNfloat f = 0.0f; f <= 1.0f; f += 1.0f/(VNfloat)quality)
    {
        glm::vec2 nextPoint = rasterizeCubicStep(previousPoint, command, f);
        vertices.emplace_back(nextPoint.x);
        vertices.emplace_back(nextPoint.y);
    }

    const glm::vec2 &lastPoint = std::get<2>(command->points);
    vertices.emplace_back(lastPoint.x);
    vertices.emplace_back(lastPoint.y);
    return vertices;
}

void Rasterizer::normalizeVertices(std::vector<VNfloat> &vertices)
{
    VNfloat longest = 0.0f;

    for (VNsize i = 0; i < vertices.size(); i+=2)
    {
        glm::vec2 vec = {vertices[i], vertices[i + 1]};
        VNfloat len = glm::length(vec);
        if (len > longest)
            longest = len;
    }
    if (longest == 0.0f)
        return;
    for (VNfloat &vert : vertices)
    {
        vert /= longest;
    }
}

std::vector<VNfloat> Rasterizer::rasterize(const Ref<Path>& path, VNuint quality)
{
    using VertexArray = std::vector<VNfloat>;
    VertexArray result;
    std::cout << "Rasterizing path: " << path->getName() << std::endl;
    glm::vec2 currentCoordinates(0.0f);
    for (const Commands::Command *command : path->getCommands())
    {
        std::cout << "Rasterizing: " << command->toString() << std::endl;
        if (command->getType() == Commands::Type::Move)
        {
            auto *moveCommand = (Commands::Move *)command;
            if (moveCommand->coordinateType == Commands::CoordinateType::Absolute)
                currentCoordinates = moveCommand->target;
            else
                currentCoordinates += moveCommand->target;
            continue;
        }
        if (command->getType() == Commands::Type::Cubic)
        {
            auto *cubic = (Commands::Cubic *)command;
            VertexArray cubicResult = Rasterizer::rasterizeCubic(currentCoordinates, cubic, quality);
            result.insert(
                    result.end(),
                    std::make_move_iterator(cubicResult.begin()),
                    std::make_move_iterator(cubicResult.end())
            );
            if (cubic->coordinateType == Commands::CoordinateType::Absolute)
                currentCoordinates = std::get<2>(cubic->points);
            else
                // Todo: test relative coordinates.
                currentCoordinates += std::get<2>(cubic->points);
            continue;
        }
        if (command->getType() == Commands::Type::VerticalLine)
        {
            auto *vline = (Commands::VLine *)command;
            result.push_back(currentCoordinates.x);
            result.push_back(currentCoordinates.y);
            if (vline->coordinateType == Commands::CoordinateType::Absolute)
            {
                result.push_back(currentCoordinates.x);
                result.push_back(vline->target);
                currentCoordinates.y = vline->target;
            }
            else
            {
                result.push_back(currentCoordinates.x);
                result.push_back(currentCoordinates.y + vline->target);
                currentCoordinates.y += vline->target;
            }
            continue;
        }
        if (command->getType() == Commands::Type::HorizontalLine)
        {
            auto *hline = (Commands::HLine *)command;
            result.push_back(currentCoordinates.x);
            result.push_back(currentCoordinates.y);
            if (hline->coordinateType == Commands::CoordinateType::Absolute)
            {
                result.push_back(hline->target);
                result.push_back(currentCoordinates.y);
                currentCoordinates.x = hline->target;
            }
            else
            {
                result.push_back(currentCoordinates.x + hline->target);
                result.push_back(currentCoordinates.y);
                currentCoordinates.x += hline->target;
            }
            continue;
        }
        if (command->getType() == Commands::Type::Line)
        {
            auto *line = (Commands::Line *)command;
            result.push_back(currentCoordinates.x);
            result.push_back(currentCoordinates.y);
            if (line->coordinateType == Commands::CoordinateType::Absolute)
            {
                result.push_back(line->target.x);
                result.push_back(line->target.y);
                currentCoordinates = line->target;
            }
            else
            {
                result.push_back(line->target.x + currentCoordinates.x);
                result.push_back(line->target.y + currentCoordinates.y);
                currentCoordinates += line->target;
            }
            continue;
        }
//        std::cout << command->toString() << " is not implemented yet." << std::endl;
    }
    return result;
}

void Rasterizer::normalize2D(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions)
{
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
            vertices[i] /= documentDimensions.x;
        else
            vertices[i] /= documentDimensions.y;
    }
}


}

}