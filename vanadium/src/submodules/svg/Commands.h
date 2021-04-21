#ifndef VANADIUM_SVG_COMMANDS_H
#define VANADIUM_SVG_COMMANDS_H

#include <glm/vec2.hpp>
#include <sstream>

#include "Types.h"

namespace Vanadium {

namespace Svg {

namespace Commands {

struct Command {
 public:
  virtual ~Command() = default;
  [[nodiscard]] virtual Commands::Type getType() const noexcept = 0;
  [[nodiscard]] virtual std::string toString() const noexcept = 0;
};

struct Move : public Command {
  const Commands::CoordinateType coordinateType;
  std::vector<glm::vec2> points;

  Move(Commands::CoordinateType coordinateType, std::vector<glm::vec2> points)
      : coordinateType(coordinateType), points(std::move(points)) {}

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::Move;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;
    ss << "Move command";
    ss << (this->coordinateType == Commands::CoordinateType::Absolute
               ? "(Absolute)"
               : "(Relative)");
    for (const auto &point : this->points) {
      ss << "(" << point.x << ", " << point.y << ") ";
    }
    return ss.str();
  }
};

struct Cubic : public Command {
  const Commands::CoordinateType coordinateType;
  std::vector<glm::vec2> points;

  Cubic(Commands::CoordinateType coordinateType, std::vector<glm::vec2> points)
      : coordinateType(coordinateType), points(std::move(points)) {}

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::Cubic;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;
    ss << "Cubic command";
    ss << (this->coordinateType == Commands::CoordinateType::Absolute
               ? "(Absolute)"
               : "(Relative)");
    ss << ": ";
    for (const auto &point : this->points) {
      ss << "(" << point.x << ", " << point.y << ") ";
    }
    return ss.str();
  }
};

struct Line : public Command {
  const Commands::CoordinateType coordinateType;
  //    const glm::vec2 target;
  std::vector<glm::vec2> points;

  Line(Commands::CoordinateType coordinateType, std::vector<glm::vec2> points)
      : coordinateType(coordinateType), points(std::move(points)) {}

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::Line;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;
    ss << "Line command";
    ss << (this->coordinateType == Commands::CoordinateType::Absolute
               ? "(Absolute)"
               : "(Relative)");
    for (const auto &point : this->points) {
      ss << ": (" << point.x << ", " << point.y << ")";
    }

    return ss.str();
  }
};

struct HLine : public Command {
  const Commands::CoordinateType coordinateType;
  std::vector<VNfloat> points;

  HLine(Commands::CoordinateType coordinateType, std::vector<VNfloat> points)
      : coordinateType(coordinateType), points(std::move(points)) {}

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::HorizontalLine;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;
    ss << "Horizontal line command";
    ss << (this->coordinateType == Commands::CoordinateType::Absolute
               ? "(Absolute)"
               : "(Relative): ");
    for (const auto &point : this->points) {
      ss << point << " ";
    }
    return ss.str();
  }
};

struct VLine : public Command {
  const Commands::CoordinateType coordinateType;
  std::vector<VNfloat> points;

  VLine(Commands::CoordinateType coordinateType, std::vector<VNfloat> points)
      : coordinateType(coordinateType), points(std::move(points)) {}

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::VerticalLine;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;
    ss << "Vertical line command";
    ss << (this->coordinateType == Commands::CoordinateType::Absolute
               ? "(Absolute)"
               : "(Relative): ");
    for (const auto &point : this->points) {
      ss << point << " ";
    }
    return ss.str();
  }
};

struct ClosePath : public Command {
  explicit ClosePath() = default;

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::ClosePath;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    return std::string("Close path command");
  }
};

// struct Quadratic : public Command
//{
//     const Commands::CoordinateType coordinateType;
////    const std::vector<glm::vec2> joints;
//    const QuadraticPoints points;
//
//    Quadratic(Commands::CoordinateType coordinateType,
//            QuadraticPoints points) :
//            coordinateType(coordinateType),
//            points(std::move(points))
//    {}
//
////    Quadratic(Commands::CoordinateType coordinateType,
////          std::vector<glm::vec2> array) :
////            coordinateType(coordinateType),
////            joints(std::move(array))
////    {}
//
//    [[nodiscard]]
//    Commands::Type getType() const noexcept override
//    {
//        return Commands::Type::Quadratic;
//    }
//
//    [[nodiscard]]
//    std::string toString() const noexcept override
//    {
//        std::stringstream ss;
//        ss << "Quadratic command";
//        ss << (this->coordinateType == Commands::CoordinateType::Absolute ?
//        "(Absolute)" : "(Relative)"); ss << ": "; ss << "(" <<
//        std::get<0>(this->points).x << ", " << std::get<0>(this->points).y <<
//        ") "; ss << "(" << std::get<1>(this->points).x << ", " <<
//        std::get<1>(this->points).y << ")"; return ss.str();
//    }
//};

struct CubicConnected : public Command {
  const Commands::CoordinateType coordinateType;
  const std::pair<glm::vec2, glm::vec2> target;

  CubicConnected(Commands::CoordinateType coordinateType,
                 std::pair<glm::vec2, glm::vec2> target)
      : coordinateType(coordinateType), target(std::move(target)) {}

  [[nodiscard]] Commands::Type getType() const noexcept override {
    return Commands::Type::CubicConnected;
  }

  [[nodiscard]] std::string toString() const noexcept override {
    std::stringstream ss;
    ss << "Cubic connected command";
    ss << (this->coordinateType == Commands::CoordinateType::Absolute
               ? "(Absolute)"
               : "(Relative)");
    ss << ": ";
    ss << "(" << this->target.first.x << ", " << this->target.first.y << "), ";
    ss << "(" << this->target.second.x << ", " << this->target.second.y << ")";
    return ss.str();
  }
};

// struct QuadraticConnected : public Command
//{
//     const Commands::CoordinateType coordinateType;
//     const glm::vec2 target;
//
//     QuadraticConnected(Commands::CoordinateType coordinateType,
//                    glm::vec2 target) :
//             coordinateType(coordinateType),
//             target(target)
//     {}
//
//     [[nodiscard]]
//     Commands::Type getType() const noexcept override
//     {
//         return Commands::Type::QuadraticConnected;
//     }
//
//     [[nodiscard]]
//     std::string toString() const noexcept override
//     {
//         std::stringstream ss;
//         ss << "Quadratic connected command";
//         ss << (this->coordinateType == Commands::CoordinateType::Absolute ?
//         "(Absolute)" : "(Relative)"); ss << ": "; ss << "(" << this->target.x
//         << ", " << this->target.y << ")"; return ss.str();
//     }
// };

}  // namespace Commands

}  // namespace Svg

}  // namespace Vanadium

#endif  // VANADIUM_SVG_COMMANDS_H
