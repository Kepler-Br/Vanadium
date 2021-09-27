#pragma once

#include <fmt/format.h>

#include <string>

#include "vanadium/core/types/LogLevel.h"

namespace vanadium {

class Logger {
 public:
  virtual ~Logger() = default;

  virtual void setLevel(LogLevel logLevel) = 0;
  virtual LogLevel getLevel() = 0;

  template <class... Args>
  void log(LogLevel logLevel, const std::string &logTemplate, Args &&...args) {
    // TODO: check whether one should log or not based on current log level.
    const std::string message =
        fmt::format(logTemplate, std::forward<Args>(args)...);

    this->log(logLevel, message);
  }

  virtual void log(LogLevel logLevel, const std::string &message) = 0;
  virtual void trace(const std::string &message) = 0;
  virtual void debug(const std::string &message) = 0;
  virtual void info(const std::string &message) = 0;
  virtual void warn(const std::string &message) = 0;
  virtual void error(const std::string &message) = 0;
  virtual void critical(const std::string &message) = 0;
};

}  // namespace vanadium
