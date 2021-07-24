#ifndef VANADIUM_TYPES_H
#define VANADIUM_TYPES_H

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>

namespace vanadium {

template <typename T>
using UniqueRef = std::unique_ptr<T>;
template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> MakeRef(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr UniqueRef<T> MakeUnique(Args &&...args) {
  return std::move(std::make_unique<T>(std::forward<Args>(args)...));
}

enum class DialogType {
  Error = 0,
  Warning,
  Information,
};

}  // namespace vanadium
#endif  // VANADIUM_TYPES_H
