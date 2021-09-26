#pragma once

#include <spdlog/fmt/bundled/core.h>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

/*
 * vec
 */
template <>
struct fmt::formatter<glm::vec4> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::vec4& vec, Context& ctx) {
    return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
  }
};

template <>
struct fmt::formatter<glm::vec3> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::vec3& vec, Context& ctx) {
    return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
  }
};

template <>
struct fmt::formatter<glm::vec2> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::vec2& vec, Context& ctx) {
    return format_to(ctx.out(), "({}, {})", vec.x, vec.y);
  }
};

/*
 * ivec.
 */
template <>
struct fmt::formatter<glm::ivec4> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::ivec4& vec, Context& ctx) {
    return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
  }
};

template <>
struct fmt::formatter<glm::ivec3> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::ivec3& vec, Context& ctx) {
    return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
  }
};

template <>
struct fmt::formatter<glm::ivec2> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::ivec2& vec, Context& ctx) {
    return format_to(ctx.out(), "({}, {})", vec.x, vec.y);
  }
};

/*
 * mat
 */
template <>
struct fmt::formatter<glm::mat4> {
  [[nodiscard]] constexpr auto parse(const format_parse_context& ctx) const {
    return ctx.end();
  }

  template <typename Context>
  auto format(const glm::mat4& mat, Context& ctx) {
    return format_to(ctx.out(), "({}, {}, {}, {})", mat[0], mat[1], mat[2],
                     mat[3]);
  }
};
