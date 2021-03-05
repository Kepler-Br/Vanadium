#include "../../core/Math.h"
#include "Rasterizer.h"
#include "Commands.h"
#include "Document.h"
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

    vertices.push_back(previousPoint.x);
    vertices.push_back(previousPoint.y);
    VNfloat delta = 1.0f/(VNfloat)quality;
    for (VNsize i = 0; i < quality; i++)
    {
        VNfloat step = (VNfloat)i * delta;
        glm::vec2 nextPoint = rasterizeCubicStep(previousPoint, command, step);
        vertices.push_back(nextPoint.x);
        vertices.push_back(nextPoint.y);
        vertices.push_back(nextPoint.x);
        vertices.push_back(nextPoint.y);
    }
    const glm::vec2 &lastPoint = std::get<2>(command->points);
    vertices.push_back(lastPoint.x);
    vertices.push_back(lastPoint.y);
    return vertices;
}

std::vector<VNfloat> Rasterizer::rasterize2D(const Ref<Path>& path, VNuint quality)
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
        std::cout << command->toString() << " is not implemented yet." << std::endl;
    }
    return result;
}

std::vector<VNfloat> Rasterizer::rasterize2D(const Ref<Document> &document, VNuint quality)
{
    std::vector<Ref<Path>> paths = document->getPaths();
    std::vector<VNfloat> vertices;
    for (const Ref<Path> &path : paths)
    {
        std::vector<VNfloat> pathVertices = Rasterizer::rasterize2D(path, quality);
        vertices.insert(
                vertices.end(),
                std::make_move_iterator(pathVertices.begin()),
                std::make_move_iterator(pathVertices.end())
        );
    }
    return vertices;
}

void Rasterizer::apply(std::vector<VNfloat> &vertices, const std::function<void(VNsize index, VNfloat &vertex)> &fun)
{
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        fun(i, vertices[i]);
    }
}

void Rasterizer::flip2D(std::vector<VNfloat> &vertices, bool x, bool y)
{
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (x && i % 2 == 0)
            vertices[i] *= -1;
        else if (y && i % 2 == 1)
            vertices[i] *= -1;
    }
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

void Rasterizer::center2D(std::vector<VNfloat> &vertices)
{
    glm::vec2 max = {vertices[0], vertices[1]};
    glm::vec2 min = {vertices[0], vertices[1]};
    glm::vec2 average;

    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
        {
            VNfloat x = vertices[i];
            if (x > max.x)
                max.x = x;
            if (x < min.x)
                min.x = x;
        }
        else
        {
            VNfloat y = vertices[i];
            if (y > max.y)
                max.y = y;
            if (y < min.y)
                min.y = y;
        }
    }
    average = {(max.x + min.x) / 2.0f,
               (max.y + min.y) / 2.0f};
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
        {
            vertices[i] -= average.x;
        }
        else
        {
            vertices[i] -= average.y;
        }
    }
}


}

}