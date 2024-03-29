#pragma once

#include <functional>
#include <vector>

#include "Commands.h"
#include "Layer.h"
#include "core/Types.h"

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
                                           const glm::vec2 &p3, uint quality);

  Rasterizer() = default;

 public:
  static std::vector<float> rasterize2D(const Path *path, uint quality);
  static std::vector<float> rasterize2D(const Layer *layer, uint quality);
  static std::vector<float> rasterize2D(const Document *document, uint quality);
};

}  // namespace vanadium::svg
