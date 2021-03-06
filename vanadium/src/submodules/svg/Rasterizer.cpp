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

glm::vec2 Rasterizer::rasterizeCubicStep(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, VNfloat t)
{
    glm::vec2 A = Math::lerp(p0, p1, t);
    glm::vec2 B = Math::lerp(p1, p2, t);
    glm::vec2 C = Math::lerp(p2, p3, t);
    glm::vec2 D = Math::lerp(A, B, t);
    glm::vec2 E = Math::lerp(B, C, t);
    glm::vec2 F = Math::lerp(D, E, t); // The juicy one

    return F;
}

std::vector<VNfloat> Rasterizer::rasterizeCubic(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, VNuint quality)
{
    std::vector<VNfloat> vertices;

    vertices.reserve((2 + quality) * 2);

    vertices.push_back(p0.x);
    vertices.push_back(p0.y);
    VNfloat delta = 1.0f/(VNfloat)quality;
    for (VNsize i = 0; i < quality; i++)
    {
        VNfloat step = (VNfloat)i * delta;
        glm::vec2 nextPoint = rasterizeCubicStep(p0, p1, p2, p3, step);

        vertices.push_back(nextPoint.x);
        vertices.push_back(nextPoint.y);
        vertices.push_back(nextPoint.x);
        vertices.push_back(nextPoint.y);
    }
    vertices.push_back(p3.x);
    vertices.push_back(p3.y);
    return vertices;
}

std::vector<VNfloat> Rasterizer::rasterize2D(const Path *path, VNuint quality)
{
    using VertexArray = std::vector<VNfloat>;
    VertexArray result;
    glm::vec2 currentCoordinates(0.0f);
    glm::vec2 pathBegin(0.0f);
    glm::vec2 lastCubicPoint(0.0f);
    const Commands::Command *previousCommand = nullptr;
    glm::vec2 lastClosePoint(0.0f);
    for (const Commands::Command *command : path->getCommands())
    {
        if (command->getType() == Commands::Type::Move)
        {
            auto *moveCommand = (Commands::Move *)command;

            if (moveCommand->coordinateType == Commands::CoordinateType::Absolute)
            {
                currentCoordinates = moveCommand->points[0];
                pathBegin = currentCoordinates;
                for (VNsize i = 1; i < moveCommand->points.size(); i++)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    currentCoordinates = moveCommand->points[i];
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                }
            }
            else
            {
                currentCoordinates += moveCommand->points[0];
                pathBegin = currentCoordinates;
                for (VNsize i = 1; i < moveCommand->points.size(); i++)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    currentCoordinates += moveCommand->points[i];
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                }
            }
        }
        else if (command->getType() == Commands::Type::Cubic)
        {
            auto *cubic = (Commands::Cubic *)command;
            VertexArray cubicResult;
            if (cubic->coordinateType == Commands::CoordinateType::Absolute)
            {
                for(VNsize i = 0; i < cubic->points.size() - 2; i+=3)
                {
                    glm::vec2 p0;
                    glm::vec2 p1;
                    glm::vec2 p2;
                    glm::vec2 p3;
                    p0 = cubic->points[i - 0];
                    p1 = cubic->points[i - -1];
                    p2 = cubic->points[i - -2];
                    cubicResult = Rasterizer::rasterizeCubic(
                            currentCoordinates,
                            p0,
                            p1,
                            p2,
                            quality);
                    currentCoordinates = cubic->points[i - -2];
                    result.insert(
                            result.end(),
                            std::make_move_iterator(cubicResult.begin()),
                            std::make_move_iterator(cubicResult.end())
                    );
                }
            }
            else
            {
                for(VNsize i = 0; i < cubic->points.size() - 2; i+=3)
                {
                    glm::vec2 p0;
                    glm::vec2 p1;
                    glm::vec2 p2;
                    glm::vec2 p3;
                    p0 = cubic->points[i - 0] + currentCoordinates;
                    p1 = cubic->points[i - -1] + currentCoordinates;
                    p2 = cubic->points[i - -2] + currentCoordinates;
                    cubicResult = Rasterizer::rasterizeCubic(
                            currentCoordinates,
                            p0,
                            p1,
                            p2,
                            quality);
                    currentCoordinates += cubic->points[i - -2];
                    result.insert(
                            result.end(),
                            std::make_move_iterator(cubicResult.begin()),
                            std::make_move_iterator(cubicResult.end())
                    );
                }
            }

            lastCubicPoint = currentCoordinates;
        }
        else if (command->getType() == Commands::Type::CubicConnected &&
            previousCommand != nullptr &&
            (previousCommand->getType() == Commands::Type::Cubic || previousCommand->getType() == Commands::Type::CubicConnected))
        {
            auto *cubic = (Commands::CubicConnected *)command;
            const std::pair<glm::vec2, glm::vec2> currentPoints = cubic->target;
            VertexArray cubicResult;
            if (cubic->coordinateType == Commands::CoordinateType::Absolute)
            {
                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
                                                         lastCubicPoint,
                                                         currentPoints.first,
                                                         currentPoints.second,
                                                         quality);

                currentCoordinates = currentPoints.second;
            }
            else
            {
                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
                                                         lastCubicPoint,
                                                         currentPoints.first + currentCoordinates,
                                                         currentPoints.second + currentCoordinates,
                                                         quality);
                currentCoordinates += currentPoints.second;

            }
            result.insert(
                    result.end(),
                    std::make_move_iterator(cubicResult.begin()),
                    std::make_move_iterator(cubicResult.end())
            );
            lastCubicPoint = currentCoordinates;
        }
        else if (command->getType() == Commands::Type::ClosePath)
        {
            result.push_back(currentCoordinates.x);
            result.push_back(currentCoordinates.y);
            result.push_back(pathBegin.x);
            result.push_back(pathBegin.y);
            currentCoordinates = pathBegin;
        }
        else if (command->getType() == Commands::Type::HorizontalLine)
        {
            auto *hline = (Commands::HLine *)command;
            if (hline->coordinateType == Commands::CoordinateType::Absolute)
            {
                for (const auto &point : hline->points)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    result.push_back(point);
                    result.push_back(currentCoordinates.y);
                }
                currentCoordinates.x = hline->points[hline->points.size() - 1];
            }
            else
            {
                for (const auto &point : hline->points)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    result.push_back(point + currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                }
                currentCoordinates.x += hline->points[hline->points.size() - 1];
            }
        }
        else if (command->getType() == Commands::Type::VerticalLine)
        {
            auto *vline = (Commands::VLine *)command;
            if (vline->coordinateType == Commands::CoordinateType::Absolute)
            {
                for (const auto &point : vline->points)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    result.push_back(currentCoordinates.x);
                    result.push_back(point);
                }
                currentCoordinates.y = vline->points[vline->points.size() - 1];
            }
            else
            {
                for (const auto &point : vline->points)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    result.push_back(currentCoordinates.x);
                    result.push_back(point + currentCoordinates.y);
                }
                currentCoordinates.y += vline->points[vline->points.size() - 1];
            }
        }
        else if (command->getType() == Commands::Type::Line)
        {
            auto *line = (Commands::Line *)command;

            if (line->coordinateType == Commands::CoordinateType::Absolute)
            {
                for (const auto &point : line->points)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    result.push_back(point.x);
                    result.push_back(point.y);
                    currentCoordinates = point;
                }

            }
            else
            {
                for (const auto &point : line->points)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    result.push_back(point.x + currentCoordinates.x);
                    result.push_back(point.y + currentCoordinates.y);
                    currentCoordinates += point;

                }

            }
        }
        else
        {
            std::cout << command->toString() << " is not implemented yet." << std::endl;
        }
        previousCommand = command;
//        std::cout << command->toString() << std::endl;
    }
    return result;
}

std::vector<VNfloat> Rasterizer::rasterize2D(const Layer *layer, VNuint quality)
{
    std::vector<VNfloat> vertices;
    std::cout << "Rasterizing layer " << layer->getName() << std::endl;
    for (const auto path : layer->getPaths())
    {

        std::vector<VNfloat> pathVertices;

        pathVertices = Rasterizer::rasterize2D(path, quality);
        vertices.insert(vertices.end(),
                        pathVertices.begin(),
                        pathVertices.end());
    }
    return vertices;
}


std::vector<VNfloat> Rasterizer::rasterize2D(const Document *document, VNuint quality)
{
    std::vector<VNfloat> vertices;

    for (const auto layer : document->getLayers())
    {
        std::vector<VNfloat> layerVertices;

        layerVertices = Rasterizer::rasterize2D(layer, quality);
        vertices.insert(vertices.end(),
                        layerVertices.begin(),
                        layerVertices.end());
    }
    return vertices;
}

}

}