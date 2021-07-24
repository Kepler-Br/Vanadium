#ifndef VANADIUM_LOG_H
#define VANADIUM_LOG_H

#include <spdlog/spdlog.h>

#include <glm/vec3.hpp>
#include <memory>

#include "LogFormatters.h"

namespace vanadium {

class Log {
 private:
  static std::shared_ptr<spdlog::logger> engineLogger;
  static std::shared_ptr<spdlog::logger> userLogger;

 public:
  static std::shared_ptr<spdlog::logger> getEngineLogger() {
    return Log::engineLogger;
  }

  static std::shared_ptr<spdlog::logger> getUserLogger() {
    return Log::userLogger;
  }

  static void init(
      spdlog::level::level_enum level = spdlog::level::level_enum::trace);
};
}  // namespace Vanadium

#ifndef VANADIUM_TURN_OFF_LOGS
#define VAN_ENGINE_TRACE(...) \
  ::vanadium::Log::getEngineLogger()->trace(__VA_ARGS__)
#define VAN_ENGINE_INFO(...) \
  ::vanadium::Log::getEngineLogger()->info(__VA_ARGS__)
#define VAN_ENGINE_WARN(...) \
  ::vanadium::Log::getEngineLogger()->warn(__VA_ARGS__)
#define VAN_ENGINE_ERROR(...) \
  ::vanadium::Log::getEngineLogger()->error(__VA_ARGS__)
#define VAN_ENGINE_CRITICAL(...) \
  ::vanadium::Log::getEngineLogger()->critical(__VA_ARGS__)

#define VAN_USER_TRACE(...) ::vanadium::Log::getUserLogger()->trace(__VA_ARGS__)
#define VAN_USER_INFO(...) ::vanadium::Log::getUserLogger()->info(__VA_ARGS__)
#define VAN_USER_WARN(...) ::vanadium::Log::getUserLogger()->warn(__VA_ARGS__)
#define VAN_USER_ERROR(...) ::vanadium::Log::getUserLogger()->error(__VA_ARGS__)
#define VAN_USER_CRITICAL(...) \
  ::vanadium::Log::getUserLogger()->critical(__VA_ARGS__)
#else
#define VAN_ENGINE_TRACE(...)
#define VAN_ENGINE_INFO(...)
#define VAN_ENGINE_WARN(...)
#define VAN_ENGINE_ERROR(...)
#define VAN_ENGINE_CRITICAL(...)

#define VAN_USER_TRACE(...)
#define VAN_USER_INFO(...)
#define VAN_USER_WARN(...)
#define VAN_USER_ERROR(...)
#define VAN_USER_CRITICAL(...)
#endif

#endif  // VANADIUM_LOG_H
