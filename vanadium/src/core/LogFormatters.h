#ifndef VANADIUM_LOGFORMATTERS_H
#define VANADIUM_LOGFORMATTERS_H

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat2x2.hpp>


/*
 * vec
 */
template <>
struct fmt::formatter<glm::vec4>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::vec4& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
    }
};

template <>
struct fmt::formatter<glm::vec3>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::vec3& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
    }
};

template <>
struct fmt::formatter<glm::vec2>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::vec2& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};

/*
 * ivec.
 */
template <>
struct fmt::formatter<glm::ivec4>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::ivec4& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
    }
};

template <>
struct fmt::formatter<glm::ivec3>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::ivec3& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
    }
};

template <>
struct fmt::formatter<glm::ivec2>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::ivec2& vec, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {})", vec.x, vec.y);
    }
};

/*
 * mat
 */
template <>
struct fmt::formatter<glm::mat4>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.end();
    }

    template <typename Context>
    auto format(const glm::mat4& mat, Context& ctx)
    {
        return format_to(ctx.out(), "({}, {}, {}, {})", mat[0], mat[1], mat[2], mat[3]);
    }
};

#endif //VANADIUM_LOGFORMATTERS_H
