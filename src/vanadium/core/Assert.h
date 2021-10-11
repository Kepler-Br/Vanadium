#pragma once

#include <fmt/printf.h>

#include "Log.h"
#ifdef VANADIUM_DEBUG
#if defined(VANADIUM_PLATFORM_WINDOWS)
#define VAN_DEBUGBREAK __debugbreak()
#elif defined(VANADIUM_PLATFORM_LINUX) || defined(VANADIUM_PLATFORM_MACOS)
#include <csignal>
#define VAN_DEBUGBREAK raise(SIGTRAP)
#else
#warning "Platform doesn't support debugbreak yet!"
#endif
#define VANADIUM_ENABLE_ASSERTS
#else
#define VAN_DEBUGBREAK
#endif

#ifdef VANADIUM_ENABLE_ASSERTS
#define VAN_ENGINE_ASSERT(condition, ...)                       \
  if (!condition) {                                             \
    VAN_ENGINE_ERROR(__VA_ARGS__);                              \
    throw std::runtime_error(                                   \
        std::string("Assertion error in file ") + __FILE__ +    \
        "; Line: " + std::to_string(__LINE__) + ". See logs."); \
  }
#define VAN_ASSERT(condition, ...)                              \
  if (!condition) {                                             \
    VAN_USER_ERROR(__VA_ARGS__);                                \
    throw std::runtime_error(                                   \
        std::string("Assertion error in file ") + __FILE__ +    \
        "; Line: " + std::to_string(__LINE__) + ". See logs."); \
  }
#else
//#define VAN_ENGINE_ASSERT(condition, ...) \
//  do if (!condition) VAN_ENGINE_ERROR(__VA_ARGS__); while(false)
#define VAN_ENGINE_ASSERT(condition, ...) \
  do if (!condition) {\
      fmt::print(stderr, fmt::format("{}:{} ", __FILE__, __LINE__) + fmt::format(__VA_ARGS__));\
      exit(EXIT_FAILURE);\
    } while(false)
#define VAN_ASSERT(condition, ...) \
  do if (!condition) VAN_USER_ERROR(__VA_ARGS__); while(false)
#endif
