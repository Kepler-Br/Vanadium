#pragma once

#include <spdlog/spdlog.h>

#include <string>

#include "core/interfaces/constructed/Logger.h"
#include "core/types/Reference.h"

namespace vanadium {

class DefaultLoggerImpl : public Logger {
 private:
  Ref<spdlog::logger> _logger;

 public:
  explicit DefaultLoggerImpl(const std::string& name,
                             std::vector<spdlog::sink_ptr>& sinks,
                             LogLevel logLevel);
  ~DefaultLoggerImpl() override = default;

  void setLevel(LogLevel logLevel) override;

  void log(LogLevel logLevel, const std::string& message) override;
  void trace(const std::string& message) override;
  void debug(const std::string& message) override;
  void info(const std::string& message) override;
  void warn(const std::string& message) override;
  void error(const std::string& message) override;
  void critical(const std::string& message) override;

};

}  // namespace vanadium
