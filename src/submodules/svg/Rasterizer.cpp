#include "submodules/svg/Rasterizer.h"

#include <iostream>

#include "core/math/Math.h"
#include "submodules/svg/Commands.h"
#include "submodules/svg/Document.h"
#include "submodules/svg/Path.h"

namespace vanadium::svg {

glm::vec2 Rasterizer::rasterizeCubicStep(const glm::vec2 &p0,
                                         const glm::vec2 &p1,
                                         const glm::vec2 &p2,
                                         const glm::vec2 &p3, float t) {
  glm::vec2 A = math::lerp(p0, p1, t);
  glm::vec2 B = math::lerp(p1, p2, t);
  glm::vec2 C = math::lerp(p2, p3, t);
  glm::vec2 D = math::lerp(A, B, t);
  glm::vec2 E = math::lerp(B, C, t);
  glm::vec2 F = math::lerp(D, E, t);  // The juicy one

  return F;
}

std::vector<float> Rasterizer::rasterizeCubic(const glm::vec2 &p0,
                                              const glm::vec2 &p1,
                                              const glm::vec2 &p2,
                                              const glm::vec2 &p3,
                                              uint quality) {
  std::vector<float> vertices;

  vertices.reserve((2 + quality) * 2);

  vertices.push_back(p0.x);
  vertices.push_back(p0.y);
  float delta = 1.0f / (float)quality;
  for (size_t i = 0; i < quality; i++) {
    float step = (float)i * delta;
    glm::vec2 nextPoint = rasterizeCubicStep(p0, p1, p2, p3, step);

    vertices.push_back(nextPoint.x);
    vertices.push_back(nextPoint.y);
    vertices.push_back(nextPoint.x);
    vertices.push_back(nextPoint.y);
  }
  vertices.push_back(p3.x);
  vertices.push_back(p3.y);
  return vertices;
}

std::vector<float> Rasterizer::rasterize2D(const Path *path, uint quality) {
  using VertexArray = std::vector<float>;
  VertexArray result;
  glm::vec2 currentCoordinates(0.0f);
  glm::vec2 pathBegin(0.0f);
  glm::vec2 lastCubicPoint(0.0f);
  const commands::Command *previousCommand = nullptr;
  glm::vec2 lastClosePoint(0.0f);
  for (const commands::Command *command : path->getCommands()) {
    if (command->getType() == commands::Type::Move) {
      auto *moveCommand = (commands::Move *)command;

      if (moveCommand->_coordinateType == commands::CoordinateType::Absolute) {
        currentCoordinates = moveCommand->_points[0];
        pathBegin = currentCoordinates;
        for (size_t i = 1; i < moveCommand->_points.size(); i++) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          currentCoordinates = moveCommand->_points[i];
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
        }
      } else {
        currentCoordinates += moveCommand->_points[0];
        pathBegin = currentCoordinates;
        for (size_t i = 1; i < moveCommand->_points.size(); i++) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          currentCoordinates += moveCommand->_points[i];
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
        }
      }
    } else if (command->getType() == commands::Type::Cubic) {
      auto *cubic = (commands::Cubic *)command;
      VertexArray cubicResult;
      if (cubic->_coordinateType == commands::CoordinateType::Absolute) {
        for (size_t i = 0; i < cubic->_points.size() - 2; i += 3) {
          glm::vec2 p0;
          glm::vec2 p1;
          glm::vec2 p2;
          glm::vec2 p3;
          p0 = cubic->_points[i - 0];
          p1 = cubic->_points[i - -1];
          p2 = cubic->_points[i - -2];
          cubicResult = Rasterizer::rasterizeCubic(currentCoordinates, p0, p1,
                                                   p2, quality);
          currentCoordinates = cubic->_points[i - -2];
          result.insert(result.end(),
                        std::make_move_iterator(cubicResult.begin()),
                        std::make_move_iterator(cubicResult.end()));
        }
      } else {
        for (size_t i = 0; i < cubic->_points.size() - 2; i += 3) {
          glm::vec2 p0;
          glm::vec2 p1;
          glm::vec2 p2;
          glm::vec2 p3;
          p0 = cubic->_points[i - 0] + currentCoordinates;
          p1 = cubic->_points[i - -1] + currentCoordinates;
          p2 = cubic->_points[i - -2] + currentCoordinates;
          cubicResult = Rasterizer::rasterizeCubic(currentCoordinates, p0, p1,
                                                   p2, quality);
          currentCoordinates += cubic->_points[i - -2];
          result.insert(result.end(),
                        std::make_move_iterator(cubicResult.begin()),
                        std::make_move_iterator(cubicResult.end()));
        }
      }

      lastCubicPoint = currentCoordinates;
    } else if (command->getType() == commands::Type::CubicConnected &&
               previousCommand != nullptr &&
               (previousCommand->getType() == commands::Type::Cubic ||
                previousCommand->getType() == commands::Type::CubicConnected)) {
      auto *cubic = (commands::CubicConnected *)command;
      const std::pair<glm::vec2, glm::vec2> currentPoints = cubic->_target;
      VertexArray cubicResult;
      if (cubic->_coordinateType == commands::CoordinateType::Absolute) {
        cubicResult = Rasterizer::rasterizeCubic(
            currentCoordinates, lastCubicPoint, currentPoints.first,
            currentPoints.second, quality);

        currentCoordinates = currentPoints.second;
      } else {
        cubicResult = Rasterizer::rasterizeCubic(
            currentCoordinates, lastCubicPoint,
            currentPoints.first + currentCoordinates,
            currentPoints.second + currentCoordinates, quality);
        currentCoordinates += currentPoints.second;
      }
      result.insert(result.end(), std::make_move_iterator(cubicResult.begin()),
                    std::make_move_iterator(cubicResult.end()));
      lastCubicPoint = currentCoordinates;
    } else if (command->getType() == commands::Type::ClosePath) {
      result.push_back(currentCoordinates.x);
      result.push_back(currentCoordinates.y);
      result.push_back(pathBegin.x);
      result.push_back(pathBegin.y);
      currentCoordinates = pathBegin;
    } else if (command->getType() == commands::Type::HorizontalLine) {
      auto *hline = (commands::HLine *)command;
      if (hline->_coordinateType == commands::CoordinateType::Absolute) {
        for (const auto &point : hline->_points) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          result.push_back(point);
          result.push_back(currentCoordinates.y);
        }
        currentCoordinates.x = hline->_points[hline->_points.size() - 1];
      } else {
        for (const auto &point : hline->_points) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          result.push_back(point + currentCoordinates.x);
          result.push_back(currentCoordinates.y);
        }
        currentCoordinates.x += hline->_points[hline->_points.size() - 1];
      }
    } else if (command->getType() == commands::Type::VerticalLine) {
      auto *vline = (commands::VLine *)command;
      if (vline->_coordinateType == commands::CoordinateType::Absolute) {
        for (const auto &point : vline->_points) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          result.push_back(currentCoordinates.x);
          result.push_back(point);
        }
        currentCoordinates.y = vline->_points[vline->_points.size() - 1];
      } else {
        for (const auto &point : vline->_points) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          result.push_back(currentCoordinates.x);
          result.push_back(point + currentCoordinates.y);
        }
        currentCoordinates.y += vline->_points[vline->_points.size() - 1];
      }
    } else if (command->getType() == commands::Type::Line) {
      auto *line = (commands::Line *)command;

      if (line->_coordinateType == commands::CoordinateType::Absolute) {
        for (const auto &point : line->_points) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          result.push_back(point.x);
          result.push_back(point.y);
          currentCoordinates = point;
        }

      } else {
        for (const auto &point : line->_points) {
          result.push_back(currentCoordinates.x);
          result.push_back(currentCoordinates.y);
          result.push_back(point.x + currentCoordinates.x);
          result.push_back(point.y + currentCoordinates.y);
          currentCoordinates += point;
        }
      }
    } else {
      std::cout << command->toString() << " is not implemented yet."
                << std::endl;
    }
    previousCommand = command;
    //        std::cout << command->toString() << std::endl;
  }
  return result;
}

std::vector<float> Rasterizer::rasterize2D(const Layer *layer, uint quality) {
  std::vector<float> vertices;
  std::cout << "Rasterizing layer " << layer->getName() << std::endl;
  for (const auto path : layer->getPaths()) {
    std::vector<float> pathVertices;

    pathVertices = Rasterizer::rasterize2D(path, quality);
    vertices.insert(vertices.end(), pathVertices.begin(), pathVertices.end());
  }
  return vertices;
}

std::vector<float> Rasterizer::rasterize2D(const Document *document,
                                           uint quality) {
  std::vector<float> vertices;

  for (const auto layer : document->getLayers()) {
    std::vector<float> layerVertices;

    layerVertices = Rasterizer::rasterize2D(layer, quality);
    vertices.insert(vertices.end(), layerVertices.begin(), layerVertices.end());
  }
  return vertices;
}

}  // namespace vanadium::svg