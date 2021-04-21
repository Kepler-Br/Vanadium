#ifndef VANADIUM_LOG_H
#define VANADIUM_LOG_H

#ifndef VANADIUM_TURN_OFF_LOGS
#include <spdlog/spdlog.h>

#include <glm/vec3.hpp>
#include <memory>

#include "LogFormatters.h"

// Todo: try to understand how it works.
namespace Vanadium {

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

// struct my_type
//{
//     template<typename OStream>
//     friend OStream &operator<<(OStream &os, const my_type &c)
//     {
//         return os << "[my_type i=" << c.i << "]";
//     }
// };

#define VAN_ENGINE_TRACE(...) \
  ::Vanadium::Log::getEngineLogger()->trace(__VA_ARGS__)
#define VAN_ENGINE_INFO(...) \
  ::Vanadium::Log::getEngineLogger()->info(__VA_ARGS__)
#define VAN_ENGINE_WARN(...) \
  ::Vanadium::Log::getEngineLogger()->warn(__VA_ARGS__)
#define VAN_ENGINE_ERROR(...) \
  ::Vanadium::Log::getEngineLogger()->error(__VA_ARGS__)
#define VAN_ENGINE_CRITICAL(...) \
  ::Vanadium::Log::getEngineLogger()->critical(__VA_ARGS__)

#define VAN_USER_TRACE(...) ::Vanadium::Log::getUserLogger()->trace(__VA_ARGS__)
#define VAN_USER_INFO(...) ::Vanadium::Log::getUserLogger()->info(__VA_ARGS__)
#define VAN_USER_WARN(...) ::Vanadium::Log::getUserLogger()->warn(__VA_ARGS__)
#define VAN_USER_ERROR(...) ::Vanadium::Log::getUserLogger()->error(__VA_ARGS__)
#define VAN_USER_CRITICAL(...) \
  ::Vanadium::Log::getUserLogger()->critical(__VA_ARGS__)

}  // namespace Vanadium
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
