#ifndef VANADIUM_TOOLS_H
#define VANADIUM_TOOLS_H

#include <functional>
#include <string>
#include <random>

#include "Types.h"

namespace Vanadium
{

namespace Tools
{

std::string randomString(const int len);

class Vertices
{
public:
    static void apply(std::vector<VNfloat> &vertices, const std::function<void(VNsize index, VNfloat &vertex)> &fun);
    static void flip2D(std::vector<VNfloat> &vertices, bool x, bool y);
    static void normalize2DDimensions(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions);
    static void normalize2D(std::vector<VNfloat> &vertices);
    static void center2D(std::vector<VNfloat> &vertices);
    static std::vector<VNuint> triangulate(const std::vector<VNfloat> &vertices);
};

}

}

#endif //VANADIUM_TOOLS_H
