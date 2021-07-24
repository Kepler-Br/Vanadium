#ifndef VANADIUM_SVG_RASTERIZER_H
#define VANADIUM_SVG_RASTERIZER_H

#include <functional>
#include <vector>

#include "core/Types.h"
#include "Commands.h"
#include "Layer.h"

namespace vanadium::svg {

class Document;
class Path;

class Rasterizer {
  static glm::vec2 rasterizeCubicStep(const glm::vec2 &p0, const glm::vec2 &p1,
                                      const glm::vec2 &p2, const glm::vec2 &p3,
                                      float t);
  static std::vector<float> rasterizeCubic(const glm::vec2 &p0,
                                             const glm::vec2 &p1,
                                             const glm::vec2 &p2,
                                             const glm::vec2 &p3,
                                             uint quality);

  Rasterizer() = default;

 public:
  static std::vector<float> rasterize2D(const Path *path, uint quality);
  static std::vector<float> rasterize2D(const Layer *layer, uint quality);
  static std::vector<float> rasterize2D(const Document *document,
                                          uint quality);
};

}  // namespace Vanadium

#endif  // VANADIUM_SVG_RASTERIZER_H
