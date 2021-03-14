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

class Vertices2D
{
public:
    static void apply(std::vector<VNfloat> &vertices, const std::function<void(VNsize index, VNfloat &vertex)> &fun);
    static void flip2D(std::vector<VNfloat> &vertices, bool x, bool y);
    static void normalize2DDimensions(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions);
    static void normalize2D(std::vector<VNfloat> &vertices);
    static void center2D(std::vector<VNfloat> &vertices);
    static glm::vec2 getCenter(const std::vector<VNfloat> &vertices);
    static glm::vec2 getBoundingBox(const std::vector<VNfloat> &vertices);
    static void applyVec2Sum(std::vector<VNfloat> &vertices, const glm::vec2 &vec);
    static void applyVec2Mul(std::vector<VNfloat> &vertices, const glm::vec2 &vec);
    static std::vector<VNuint> triangulate(const std::vector<VNfloat> &vertices);
    static std::vector<VNfloat> interpolate(const std::vector<VNfloat> &start, const std::vector<VNfloat> &end, VNfloat t);
    static void interpolate(const std::vector<VNfloat> &start, const std::vector<VNfloat> &end, std::vector<VNfloat> &output, VNfloat t);
};

}

}

#endif //VANADIUM_TOOLS_H
