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
  virtual bool shouldLog(LogLevel logLevel) = 0;

  virtual void log(LogLevel logLevel, const std::string &message) = 0;
  virtual void trace(const std::string &message) = 0;
  virtual void debug(const std::string &message) = 0;
  virtual void info(const std::string &message) = 0;
  virtual void warn(const std::string &message) = 0;
  virtual void error(const std::string &message) = 0;
  virtual void critical(const std::string &message) = 0;

#pragma region template
  template <class... Args>
  void log(LogLevel logLevel, const std::string &logTemplate, Args &&...args);

  template <class... Args>
  void trace(const std::string &logTemplate, Args &&...args);

  template <class... Args>
  void debug(const std::string &logTemplate, Args &&...args);

  template <class... Args>
  void info(const std::string &logTemplate, Args &&...args);

  template <class... Args>
  void warn(const std::string &logTemplate, Args &&...args);

  template <class... Args>
  void error(const std::string &logTemplate, Args &&...args);

  template <class... Args>
  void critical(const std::string &logTemplate, Args &&...args);
#pragma endregion
};

#pragma region template definitions
template <class... Args>
void Logger::log(LogLevel logLevel, const std::string &logTemplate,
                 Args &&...args) {
  if(!this->shouldLog(logLevel)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->log(logLevel, message);
}

template <class... Args>
void Logger::trace(const std::string &logTemplate, Args &&...args) {
  if(!this->shouldLog(LogLevel::Trace)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->trace(message);
}

template <class... Args>
void Logger::debug(const std::string &logTemplate, Args &&...args) {
  if(!this->shouldLog(LogLevel::Debug)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->debug(message);
}

template <class... Args>
void Logger::info(const std::string &logTemplate, Args &&...args) {
  if(!this->shouldLog(LogLevel::Info)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->info(message);
}

template <class... Args>
void Logger::warn(const std::string &logTemplate, Args &&...args) {
  if(!this->shouldLog(LogLevel::Warn)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->warn(message);
}

template <class... Args>
void Logger::error(const std::string &logTemplate, Args &&...args) {
  if(!this->shouldLog(LogLevel::Error)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->error(message);
}

template <class... Args>
void Logger::critical(const std::string &logTemplate, Args &&...args) {
  if(!this->shouldLog(LogLevel::Critical)) {
    return;
  }

  const std::string message =
      fmt::format(logTemplate, std::forward<Args>(args)...);

  this->critical(message);
}
#pragma endregion

}  // namespace vanadium
