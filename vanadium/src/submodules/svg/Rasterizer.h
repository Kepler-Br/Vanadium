#ifndef VANADIUM_SVG_RASTERIZER_H
#define VANADIUM_SVG_RASTERIZER_H

#include <functional>
#include <vector>

#include "../../core/Types.h"
#include "Commands.h"
#include "Layer.h"

namespace Vanadium {

namespace Svg {

class Document;
class Path;

class Rasterizer {
  static glm::vec2 rasterizeCubicStep(const glm::vec2 &p0, const glm::vec2 &p1,
                                      const glm::vec2 &p2, const glm::vec2 &p3,
                                      VNfloat t);
  static std::vector<VNfloat> rasterizeCubic(const glm::vec2 &p0,
                                             const glm::vec2 &p1,
                                             const glm::vec2 &p2,
                                             const glm::vec2 &p3,
                                             VNuint quality);

  Rasterizer() = default;

 public:
  static std::vector<VNfloat> rasterize2D(const Path *path, VNuint quality);
  static std::vector<VNfloat> rasterize2D(const Layer *layer, VNuint quality);
  static std::vector<VNfloat> rasterize2D(const Document *document,
                                          VNuint quality);
};

}  // namespace Svg

}  // namespace Vanadium

#endif  // VANADIUM_SVG_RASTERIZER_H
