#pragma once

#include <spdlog/spdlog.h>

#include "core/interfaces/constructed/factories/LoggerFactory.h"
#include "core/types/Reference.h"

namespace vanadium {

class DefaultLoggerFactoryImpl : public LoggerFactory {
 private:
  std::vector<Ref<spdlog::sinks::sink>> _sinks;
  LogLevel _logLevel;

 public:
  DefaultLoggerFactoryImpl(const std::string &filename, bool writeFile, LogLevel logLevel);
  ~DefaultLoggerFactoryImpl() override = default;

  Ref<Logger> construct(const std::string &name) override;
};

}  // namespace vanadium
