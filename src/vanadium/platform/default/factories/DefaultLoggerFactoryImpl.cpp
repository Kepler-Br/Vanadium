#include "DefaultLoggerFactoryImpl.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "vanadium/platform/default/DefaultLoggerImpl.h"
#include "vanadium/platform/default/SpdLogLevelConvertor.h"

namespace vanadium {

const std::string DefaultLoggerFactoryImpl::_implName =
    "DefaultLoggerFactoryImpl";

Ref<spdlog::logger> DefaultLoggerFactoryImpl::createLogger(
    const std::string &name, LogLevel logLevel) const {
  Ref<spdlog::logger> logger = spdlog::get(name);

  if (logger == nullptr) {
    logger =
        MakeRef<spdlog::logger>(name, begin(this->_sinks), end(this->_sinks));

    spdlog::register_logger(logger);
  }

  spdlog::level::level_enum level = toSpdLogLevel(logLevel);

  logger->set_level(level);

  return logger;
}

DefaultLoggerFactoryImpl::DefaultLoggerFactoryImpl(LogLevel logLevel,
                                                   const std::string &pattern,
                                                   const std::string &filename)
    : _logLevel(logLevel) {
  using namespace spdlog;

#if defined(VANADIUM_PLATFORM_LINUX) || defined(VANADIUM_PLATFORM_MACOS)
  Ref<sinks::stdout_color_sink_mt> colorSink =
      MakeRef<spdlog::sinks::stdout_color_sink_mt>();
#elif VANADIUM_PLATFORM_WINDOWS
  Ref<sinks::wincolor_stdout_sink_mt> colorSink =
      MakeRef<spdlog::sinks::wincolor_stdout_sink_mt>();
#endif

  colorSink->set_pattern(pattern);

  this->_sinks.emplace_back(colorSink);

  if (!filename.empty()) {
    Ref<sinks::basic_file_sink_mt> fileSink =
        MakeRef<spdlog::sinks::basic_file_sink_mt>(filename, true);

    fileSink->set_pattern(pattern);

    this->_sinks.emplace_back(fileSink);
  }
}

Ref<Logger> DefaultLoggerFactoryImpl::construct(const std::string &name) {
  Ref<spdlog::logger> logger = this->createLogger(name, this->_logLevel);

  return MakeRef<DefaultLoggerImpl>(logger);
}

Ref<Logger> DefaultLoggerFactoryImpl::construct(const std::string &name,
                                                LogLevel logLevel) {
  Ref<spdlog::logger> logger = this->createLogger(name, logLevel);

  return MakeRef<DefaultLoggerImpl>(logger);
}

const std::string &DefaultLoggerFactoryImpl::getImplName() const noexcept {
  return DefaultLoggerFactoryImpl::_implName;
}

}  // namespace vanadium
