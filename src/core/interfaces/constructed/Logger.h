#pragma once

#include <string>

#include "core/types/LogLevel.h"

namespace vanadium {

class Logger {
 public:
  virtual ~Logger() = default;

  virtual void setLevel(LogLevel logLevel) = 0;

  virtual void log(LogLevel logLevel, const std::string &message) = 0;
  virtual void trace(const std::string &message) = 0;
  virtual void debug(const std::string &message) = 0;
  virtual void info(const std::string &message) = 0;
  virtual void warn(const std::string &message) = 0;
  virtual void error(const std::string &message) = 0;
  virtual void critical(const std::string &message) = 0;
};

}  // namespace vanadium
