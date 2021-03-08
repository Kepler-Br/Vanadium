#include "Tools.h"
#include "../vendor/earcuthpp/earcut.hpp"
#include "Math.h"
#include <tuple>

namespace Vanadium
{

namespace Tools
{


void Vertices2D::apply(std::vector<VNfloat> &vertices, const std::function<void(VNsize index, VNfloat &vertex)> &fun)
{
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        fun(i, vertices[i]);
    }
}

void Vertices2D::flip2D(std::vector<VNfloat> &vertices, bool x, bool y)
{
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (x && (i % 2 == 0))
            vertices[i] *= -1;
        else if (y && (i % 2 == 1))
            vertices[i] *= -1;
    }
}

void Vertices2D::normalize2DDimensions(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions)
{
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
            vertices[i] /= documentDimensions.x;
        else
            vertices[i] /= documentDimensions.y;
    }
}

void Vertices2D::normalize2D(std::vector<VNfloat> &vertices)
{
    glm::vec2 max = {vertices[0], vertices[1]};
    glm::vec2 min = {vertices[0], vertices[1]};

    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
        {
            if (vertices[i] > max.x)
                max.x = vertices[i];
            if (vertices[i] < min.x)
                min.x = vertices[i];
        }
        else
        {
            if (vertices[i] > max.y)
                max.y = vertices[i];
            if (vertices[i] < min.y)
                min.y = vertices[i];
        }
    }
    glm::vec2 average = {(glm::abs(max.x) + glm::abs(min.x)) / 2.0f,
                         (glm::abs(max.y) + glm::abs(min.y)) / 2.0f,};
    for (VNsize i = 0; i < vertices.size(); i++)
    {
        if (i % 2 == 0)
            vertices[i] /= average.x;
        else
            vertices[i] /= average.y;
    }
}

void Vertices2D::center2D(std::vector<VNfloat> &vertices)
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


std::vector<VNuint> Vertices2D::triangulate(const std::vector<VNfloat> &vertices)
{
//    using Point = std::array<float, 2>;
//    std::vector<std::vector<Point>> points;
//    points.emplace_back();
//    for (VNsize i = 0; i < vertices.size(); i += 2)
//    {
//        points[0].push_back({vertices[i], vertices[i+1]});
//    }
    std::vector<VNuint> indices = mapbox::earcut<VNuint>(vertices);
//    std::vector<VNuint> indices = mapbox::earcut<VNuint>(points);
    return indices;
}

std::vector<VNfloat> Vertices2D::interpolate(const std::vector<VNfloat> &start, const std::vector<VNfloat> &end, VNfloat t)
{
    std::vector<VNfloat> interpolated;

    if (start.size() != end.size())
    {
        return interpolated;
    }
    interpolated.reserve(start.size());
    for (VNsize i = 0; i < start.size(); i++)
    {
        interpolated.push_back(Math::lerp(start[i], end[i], t));
    }
    return interpolated;
}

void Vertices2D::interpolate(const std::vector<VNfloat> &start, const std::vector<VNfloat> &end, std::vector<VNfloat> &output, VNfloat t)
{
    if (start.size() != end.size())
    {
        return;
    }
    if (output.size() != start.size())
    {
        output.resize(start.size());
    }
    for (VNsize i = 0; i < start.size(); i++)
    {
        output[i] = Math::lerp(start[i], end[i], t);
    }
}

std::string randomString(const int len)
{
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[random() % (sizeof(alphanum) - 1)];
    return tmp_s;
}
}

}
