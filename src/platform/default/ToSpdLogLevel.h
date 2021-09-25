#pragma once

#include <spdlog/common.h>

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
    case LogLevel::Warn:
      return level::warn;
    case LogLevel::Error:
      return level::err;
    case LogLevel::Critical:
      return level::critical;
    default:
      return level::off;
  }
}

}  // namespace vanadium
