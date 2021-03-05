#ifndef VANADIUM_SVG_RASTERIZER_H
#define VANADIUM_SVG_RASTERIZER_H

#include <vector>

#include "../../core/Types.h"
#include "Commands.h"
#include "Layer.h"


namespace Vanadium
{

namespace Svg
{

class Document;
class Path;

class Rasterizer
{
    static glm::vec2 rasterizeCubicStep(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, VNfloat t);
    static std::vector<VNfloat> rasterizeCubic(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, VNuint quality);

    Rasterizer() = default;

public:

    static std::vector<VNfloat> rasterize2D(const Path *path, VNuint quality);
    static std::vector<VNfloat> rasterize2D(const Layer *layer, VNuint quality);
    static std::vector<VNfloat> rasterize2D(const Document *document, VNuint quality);

    static void apply(std::vector<VNfloat> &vertices, const std::function<void(VNsize index, VNfloat &vertex)> &fun);
    static void flip2D(std::vector<VNfloat> &vertices, bool x, bool y);
    static void normalize2D(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions);
    static void center2D(std::vector<VNfloat> &vertices);

};

}

}

#endif //VANADIUM_SVG_RASTERIZER_H
