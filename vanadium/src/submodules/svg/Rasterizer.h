#ifndef VANADIUM_SVG_RASTERIZER_H
#define VANADIUM_SVG_RASTERIZER_H

#include <vector>

#include "../../core/Types.h"
#include "Commands.h"


namespace Vanadium
{

namespace Svg
{

class Document;
class Path;

class Rasterizer
{
    static glm::vec2 rasterizeCubicStep(const glm::vec2 &previousPoint, const Commands::Cubic *command, VNfloat t);
    static std::vector<VNfloat> rasterizeCubic(const glm::vec2 &previousPoint, const Commands::Cubic *command, VNuint quality);

    Rasterizer() = default;

public:

    static std::vector<VNfloat> rasterize2D(const Ref<Path>& path, VNuint quality);
    static std::vector<VNfloat> rasterize2D(const Ref<Document> &document, VNuint quality);
    static void apply(std::vector<VNfloat> &vertices, const std::function<void(VNsize index, VNfloat &vertex)> &fun);
    static void flip2D(std::vector<VNfloat> &vertices, bool x, bool y);
    static void normalize2D(std::vector<VNfloat> &vertices, const glm::vec2 &documentDimensions);
    static void center2D(std::vector<VNfloat> &vertices);

};

}

}

#endif //VANADIUM_SVG_RASTERIZER_H
