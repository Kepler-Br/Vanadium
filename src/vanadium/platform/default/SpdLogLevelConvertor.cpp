#include "SpdLogLevelConvertor.h"

namespace vanadium {

spdlog::level::level_enum toSpdLogLevel(LogLevel logLevel) {
  using namespace spdlog;

  switch (logLevel) {
    case LogLevel::Off:
      return level::off;
    case LogLevel::Trace:
      return level::trace;
    case LogLevel::Debug:
      return level::debug;
    case LogLevel::Info:
      return level::info;
    case LogLevel::Warning:
      return level::warn;
    case LogLevel::Error:
      return level::err;
    case LogLevel::Critical:
      return level::critical;
    default:
      return level::off;
  }
}

LogLevel fromSpdLogLevel(spdlog::level::level_enum logLevel) {
  using namespace spdlog;

  switch (logLevel) {
    case level::off:
      return LogLevel::Off;
    case level::trace:
      return LogLevel::Trace;
    case level::debug:
      return LogLevel::Debug;
    case level::info:
      return LogLevel::Info;
    case level::warn:
      return LogLevel::Warning;
    case level::err:
      return LogLevel::Error;
    case level::critical:
      return LogLevel::Critical;
    default:
      return LogLevel::Off;
  }
}

}  // namespace vanadium
