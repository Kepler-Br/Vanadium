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
//    glm::vec2 lastCubicPoint(0.0f);
//    const Commands::Command *previousCommand = nullptr;
    for (const Commands::Command *command : path->getCommands())
    {
        if (command->getType() == Commands::Type::Move)
        {
            auto *moveCommand = (Commands::Move *)command;

            if (moveCommand->coordinateType == Commands::CoordinateType::Absolute)
                currentCoordinates = moveCommand->target;
            else
                currentCoordinates += moveCommand->target;
            pathBegin = currentCoordinates;
        }
        else if (command->getType() == Commands::Type::Cubic)
        {
            auto *cubic = (Commands::Cubic *)command;
            VertexArray cubicResult;
            if (cubic->coordinateType == Commands::CoordinateType::Absolute)
            {
                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
                                                         cubic->points[0],
                                                         cubic->points[1],
                                                         cubic->points[2],
                                                         quality);
                result.insert(
                        result.end(),
                        std::make_move_iterator(cubicResult.begin()),
                        std::make_move_iterator(cubicResult.end())
                );
                currentCoordinates = cubic->points[cubic->points.size() - 1];
//                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
//                                                         std::get<0>(cubic->points),
//                                                         std::get<1>(cubic->points),
//                                                         std::get<2>(cubic->points),
//                                                         quality);
//                currentCoordinates = std::get<2>(cubic->points);


//                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
//                                                         cubic->points[0],
//                                                         cubic->points[1],
//                                                         cubic->points[2],
//                                                         quality);
//                result.insert(
//                        result.end(),
//                        std::make_move_iterator(cubicResult.begin()),
//                        std::make_move_iterator(cubicResult.end())
//                );
//                for(VNsize i = 3; i < cubic->points.size(); i+=3)
//                {
//                    cubicResult = Rasterizer::rasterizeCubic(cubic->points[i-3],
//                                                             cubic->points[i-2],
//                                                             cubic->points[i-1],
//                                                             cubic->points[i],
//                                                             quality);
//                    result.insert(
//                            result.end(),
//                            std::make_move_iterator(cubicResult.begin()),
//                            std::make_move_iterator(cubicResult.end())
//                            );
//                }
//                currentCoordinates = cubic->points[cubic->points.size() - 1];
                std::cout << "Oh shit oh fuck!" << std::endl;
            }
            else
            {

                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
                                                         cubic->points[0] + currentCoordinates,
                                                         cubic->points[1] + currentCoordinates,
                                                         cubic->points[2] + currentCoordinates,
                                                         quality);
                result.insert(
                        result.end(),
                        std::make_move_iterator(cubicResult.begin()),
                        std::make_move_iterator(cubicResult.end())
                );
//                result.push_back(currentCoordinates.x);
//                result.push_back(currentCoordinates.y);
//                result.push_back(cubic->points[2].x + currentCoordinates.x);
//                result.push_back(cubic->points[2].y + currentCoordinates.y);
                currentCoordinates += cubic->points[2];
                for(VNsize i = 3; i < cubic->points.size(); i+=2)
                {
                    result.push_back(currentCoordinates.x);
                    result.push_back(currentCoordinates.y);
                    glm::vec2 p0;
                    p0 = cubic->points[i] + currentCoordinates;
                    result.push_back(p0.x);
                    result.push_back(p0.y);
                    currentCoordinates += cubic->points[i];

//                    glm::vec2 p0;
//                    glm::vec2 p1;
//                    glm::vec2 p2;
//                    glm::vec2 p3;
//                    p0 = cubic->points[i - 1] + currentCoordinates;
//                    p1 = cubic->points[i + 0] + currentCoordinates;
//                    p2 = cubic->points[i + 1] + currentCoordinates;
//                    p3 = cubic->points[i + 1] + currentCoordinates;
//                    cubicResult = Rasterizer::rasterizeCubic(
//                                                             currentCoordinates,
//                                                             p0,
//                                                             p1,
//                                                             p2,
//                                                             quality);
//                    currentCoordinates += cubic->points[i + -1];

//                    std::cout << "Generated: ";
//                    for (VNsize j = 0; j < cubicResult.size(); j+=2)
//                    {
//                        std::cout << "(" << cubicResult[j] << ", " << cubicResult[j + 1] << ") ";
//                    }
//                    std::cout << std::endl;
//                    std::cout << "-----------------" << std::endl;
                    result.insert(
                            result.end(),
                            std::make_move_iterator(cubicResult.begin()),
                            std::make_move_iterator(cubicResult.end())
                    );
                }

//                currentCoordinates += cubic->points[cubic->points.size() - 1];
//                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
//                                                         std::get<0>(cubic->points) + currentCoordinates,
//                                                         std::get<1>(cubic->points) + currentCoordinates,
//                                                         std::get<2>(cubic->points) + currentCoordinates,
//                                                         quality);
//                currentCoordinates += std::get<2>(cubic->points);

            }

//            lastCubicPoint = currentCoordinates;
        }
//        else if (command->getType() == Commands::Type::CubicConnected &&
//            previousCommand != nullptr &&
//            (previousCommand->getType() == Commands::Type::Cubic || previousCommand->getType() == Commands::Type::CubicConnected))
//        {
//            auto *cubic = (Commands::CubicConnected *)command;
//            const std::pair<glm::vec2, glm::vec2> currentPoints = cubic->target;
//            VertexArray cubicResult;
//            if (cubic->coordinateType == Commands::CoordinateType::Absolute)
//            {
//                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
//                                                         lastCubicPoint,
//                                                         currentPoints.first,
//                                                         currentPoints.second,
//                                                         quality);
//
//                currentCoordinates = currentPoints.second;
//            }
//            else
//            {
//                // Todo: test relative coordinates.
//                cubicResult = Rasterizer::rasterizeCubic(currentCoordinates,
//                                                         lastCubicPoint,
//                                                         currentPoints.first + currentCoordinates,
//                                                         currentPoints.second + currentCoordinates,
//                                                         quality);
//                currentCoordinates += currentPoints.second;
//
//            }
//            result.insert(
//                    result.end(),
//                    std::make_move_iterator(cubicResult.begin()),
//                    std::make_move_iterator(cubicResult.end())
//            );
//            lastCubicPoint = currentCoordinates;
//        }
        else if (command->getType() == Commands::Type::ClosePath)
        {
            result.push_back(currentCoordinates.x);
            result.push_back(currentCoordinates.y);
            result.push_back(pathBegin.x);
            result.push_back(pathBegin.y);
            currentCoordinates = pathBegin;
        }
//        else if (command->getType() == Commands::Type::HorizontalLine)
//        {
//            auto *hline = (Commands::HLine *)command;
//            result.push_back(currentCoordinates.x);
//            result.push_back(currentCoordinates.y);
//            if (hline->coordinateType == Commands::CoordinateType::Absolute)
//            {
//                result.push_back(hline->target);
//                result.push_back(currentCoordinates.y);
//                currentCoordinates.x = hline->target;
//            }
//            else
//            {
//                result.push_back(currentCoordinates.x + hline->target);
//                result.push_back(currentCoordinates.y);
//                currentCoordinates.x += hline->target;
//            }
//        }
//        else if (command->getType() == Commands::Type::VerticalLine)
//        {
//            auto *vline = (Commands::VLine *)command;
//            result.push_back(currentCoordinates.x);
//            result.push_back(currentCoordinates.y);
//            if (vline->coordinateType == Commands::CoordinateType::Absolute)
//            {
//                result.push_back(currentCoordinates.x);
//                result.push_back(vline->target);
//                currentCoordinates.y = vline->target;
//            }
//            else
//            {
//                result.push_back(currentCoordinates.x);
//                result.push_back(currentCoordinates.y + vline->target);
//                currentCoordinates.y += vline->target;
//            }
//        }
        else if (command->getType() == Commands::Type::Line)
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

        }
        else
        {
            std::cout << command->toString() << " is not implemented yet." << std::endl;
        }
//        previousCommand = command;
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
    if (vertices.size() < 2)
        return;
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