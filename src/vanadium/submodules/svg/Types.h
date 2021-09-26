#pragma once

namespace vanadium::svg {

// Three because first point is previous point.
using CubicPoints = std::tuple<glm::vec2, glm::vec2, glm::vec2>;
using QuadraticPoints = std::tuple<glm::vec2, glm::vec2>;

namespace commands {

enum class Type {
  Unknown,
  Move,
  Line,
  HorizontalLine,
  VerticalLine,
  ClosePath,
  Cubic,
  Quadratic,
  CubicConnected,
  QuadraticConnected,
};

enum class CoordinateType {
  Unknown,
  Absolute,
  Relative,
};

}  // namespace commands

}  // namespace vanadium::svg
