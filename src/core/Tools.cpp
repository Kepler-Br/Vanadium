#include "core/Tools.h"

#include <earcut.hpp>
#include <glm/glm.hpp>

#include "core/math/Math.h"

namespace vanadium::tools {

void Vertices2D::flip2D(std::vector<float> &vertices, bool x, bool y) {
  if (!x && !y) {
    return;
  }
  for (size_t i = 0; i < vertices.size(); i++) {
    if (x && (i % 2 == 0)) {
      vertices[i] *= -1;
    } else if (y && (i % 2 == 1)) {
      vertices[i] *= -1;
    }
  }
}

void Vertices2D::normalize2DDimensions(std::vector<float> &vertices,
                                       const glm::vec2 &documentDimensions) {
  for (size_t i = 0; i < vertices.size(); i++) {
    if (i % 2 == 0) {
      vertices[i] /= documentDimensions.x;
    } else {
      vertices[i] /= documentDimensions.y;
    }
  }
}

void Vertices2D::normalize2D(std::vector<float> &vertices) {
  glm::vec2 max = {vertices[0], vertices[1]};
  glm::vec2 min = {vertices[0], vertices[1]};

  for (size_t i = 0; i < vertices.size(); i++) {
    if (i % 2 == 0) {
      if (vertices[i] > max.x) max.x = vertices[i];
      if (vertices[i] < min.x) min.x = vertices[i];
    } else {
      if (vertices[i] > max.y) max.y = vertices[i];
      if (vertices[i] < min.y) min.y = vertices[i];
    }
  }
  glm::vec2 average = {
      (glm::abs(max.x) + glm::abs(min.x)) / 2.0f,
      (glm::abs(max.y) + glm::abs(min.y)) / 2.0f,
  };
  for (size_t i = 0; i < vertices.size(); i++) {
    if (i % 2 == 0) {
      vertices[i] /= average.x;
    } else {
      vertices[i] /= average.y;
    }
  }
}

void Vertices2D::center2D(std::vector<float> &vertices) {
  if (vertices.size() < 2) {
    return;
  }
  glm::vec2 average = Vertices2D::getCenter(vertices);
  for (size_t i = 0; i < vertices.size(); i++) {
    if (i % 2 == 0) {
      vertices[i] -= average.x;
    } else {
      vertices[i] -= average.y;
    }
  }
}

glm::vec2 Vertices2D::getCenter(const std::vector<float> &vertices) {
  if (vertices.size() < 2) {
    return glm::vec2(0.0f);
  }
  glm::vec2 max = {vertices[0], vertices[1]};
  glm::vec2 min = {vertices[0], vertices[1]};

  for (size_t i = 0; i < vertices.size(); i++) {
    if (i % 2 == 0) {
      float x = vertices[i];
      if (x > max.x) {
        max.x = x;
      }
      if (x < min.x) {
        min.x = x;
      }
    } else {
      float y = vertices[i];
      if (y > max.y) {
        max.y = y;
      }
      if (y < min.y) {
        min.y = y;
      }
    }
  }
  return {(max.x + min.x) / 2.0f, (max.y + min.y) / 2.0f};
}

glm::vec2 Vertices2D::getBoundingBox(const std::vector<float> &vertices) {
  if (vertices.size() < 2) {
    return glm::vec2(0.0f);
  }
  glm::vec2 center = Vertices2D::getCenter(vertices);
  glm::vec2 boundingBox(0.0f);
  for (size_t i = 0; i < vertices.size(); i += 2) {
    float x = vertices[i] - center.x;
    float y = vertices[i + 1] - center.y;
    if (glm::abs(boundingBox.x) < glm::abs(x)) {
      boundingBox.x = x;
    }
    if (glm::abs(boundingBox.y) < glm::abs(y)) {
      boundingBox.y = y;
    }
  }
  return boundingBox;
}

void Vertices2D::applyVec2Sum(std::vector<float> &vertices,
                              const glm::vec2 &vec) {
  if (vertices.size() < 2) {
    return;
  }
  for (size_t i = 0; i < vertices.size(); i += 2) {
    vertices[i] += vec.x;
    vertices[i + 1] += vec.y;
  }
}

void Vertices2D::applyVec2Mul(std::vector<float> &vertices,
                              const glm::vec2 &vec) {
  if (vertices.size() < 2) {
    return;
  }
  for (size_t i = 0; i < vertices.size(); i += 2) {
    vertices[i] *= vec.x;
    vertices[i + 1] *= vec.y;
  }
}

std::vector<uint16_t> Vertices2D::triangulate(
    const std::vector<float> &vertices) {
  std::vector<uint16_t> indices = mapbox::earcut<uint16_t>(vertices);

  return indices;
}

std::vector<float> Vertices2D::interpolate(const std::vector<float> &start,
                                           const std::vector<float> &end,
                                           float t) {
  std::vector<float> interpolated;

  if (start.size() != end.size()) {
    return interpolated;
  }
  interpolated.reserve(start.size());
  for (size_t i = 0; i < start.size(); i++) {
    interpolated.push_back(math::lerp(start[i], end[i], t));
  }
  return interpolated;
}

void Vertices2D::interpolate(const std::vector<float> &start,
                             const std::vector<float> &end,
                             std::vector<float> &output, float t) {
  if (start.size() != end.size()) {
    return;
  }
  if (output.size() != start.size()) {
    output.resize(start.size());
  }
  for (size_t i = 0; i < start.size(); i++) {
    output[i] = math::lerp(start[i], end[i], t);
  }
}

}  // namespace vanadium::tools
