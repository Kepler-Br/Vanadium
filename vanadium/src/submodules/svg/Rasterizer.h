#ifndef VANADIUM_SVG_RASTERIZER_H
#define VANADIUM_SVG_RASTERIZER_H

#include <vector>

#include "../../core/Types.h"
#include "Commands.h"

namespace Vanadium
{

namespace Svg
{

class Path;

class Rasterizer
{
    static glm::vec2 rasterizeCubicStep(const glm::vec2 &previousPoint, const Commands::Cubic *command, VNfloat t);
    static std::vector<VNfloat> rasterizeCubic(const glm::vec2 &previousPoint, const Commands::Cubic *command, VNuint quality);
    static void normalizeVertices(std::vector<VNfloat> &vertices);

public:
    Rasterizer() = delete;

//    static std::vector<VNfloat> strip2D(const Ref<Path>& path, VNuint quality);
    static std::vector<VNfloat> rasterize(const Ref<Path>& path, VNuint quality);
    static void normalize2D(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions);

};

}

}

#endif //VANADIUM_SVG_RASTERIZER_H
