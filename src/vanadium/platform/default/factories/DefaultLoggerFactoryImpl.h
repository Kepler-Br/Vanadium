#pragma once

#include <spdlog/spdlog.h>

#include "vanadium/core/interfaces/constructed/factories/LoggerFactory.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class DefaultLoggerFactoryImpl : public LoggerFactory {
 private:
  static const std::string _implName;

  std::vector<Ref<spdlog::sinks::sink>> _sinks;
  LogLevel _logLevel;

 public:
  explicit DefaultLoggerFactoryImpl(
      LogLevel logLevel,
      const std::string &pattern = "[%Y-%m-%d %T] [%l] %n: %v",
      bool writeFile = false, const std::string &filename = "");
  ~DefaultLoggerFactoryImpl() override = default;

  Ref<Logger> construct(const std::string &name) override;

  [[nodiscard]] const std::string &getImplName() const noexcept override;
};

}  // namespace vanadium
