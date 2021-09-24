#pragma once

#include <functional>
#include <glm/vec2.hpp>
#include <random>
#include <string>

namespace vanadium::tools {

std::string randomString(int len);

class Vertices2D {
 public:
  template<class TApplyFunction>
  static void apply(std::vector<float> &vertices, TApplyFunction &applyFunction) {
    for (size_t i = 0; i < vertices.size(); i++) {
      applyFunction(i, vertices[i]);
    }
  }

  static void flip2D(std::vector<float> &vertices, bool x, bool y);
  static void normalize2DDimensions(std::vector<float> &vertices,
                                    const glm::vec2 &documentDimensions);
  static void normalize2D(std::vector<float> &vertices);
  static void center2D(std::vector<float> &vertices);
  static glm::vec2 getCenter(const std::vector<float> &vertices);
  static glm::vec2 getBoundingBox(const std::vector<float> &vertices);
  static void applyVec2Sum(std::vector<float> &vertices, const glm::vec2 &vec);
  static void applyVec2Mul(std::vector<float> &vertices, const glm::vec2 &vec);
  static std::vector<uint16_t> triangulate(const std::vector<float> &vertices);
  static std::vector<float> interpolate(const std::vector<float> &start,
                                        const std::vector<float> &end, float t);
  static void interpolate(const std::vector<float> &start,
                          const std::vector<float> &end,
                          std::vector<float> &output, float t);
};

}  // namespace vanadium::tools
