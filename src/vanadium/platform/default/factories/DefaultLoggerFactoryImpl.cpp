#include "DefaultLoggerFactoryImpl.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "vanadium/platform/default/DefaultLoggerImpl.h"

namespace vanadium {

const std::string DefaultLoggerFactoryImpl::_implName =
    "DefaultLoggerFactoryImpl";

DefaultLoggerFactoryImpl::DefaultLoggerFactoryImpl(LogLevel logLevel,
                                                   const std::string &pattern,
                                                   bool writeFile,
                                                   const std::string &filename)
    : _logLevel(logLevel) {
  using namespace spdlog;

#if defined(VANADIUM_PLATFORM_LINUX) || defined(VANADIUM_PLATFORM_MACOS)
  Ref<sinks::stdout_color_sink_mt> colorSink =
      MakeRef<spdlog::sinks::stdout_color_sink_mt>();
  colorSink->set_color_mode(color_mode::always);
//  colorSink->set_color(spdlog::level::warn, "\033[37m");
//  colorSink->set_color(spdlog::level::critical, colorSink->blue);
#elif VANADIUM_PLATFORM_WINDOWS
  Ref<sinks::wincolor_stdout_sink_mt> colorSink =
      MakeRef<spdlog::sinks::wincolor_stdout_sink_mt>();
#endif

  colorSink->set_pattern(pattern);

  this->_sinks.emplace_back(colorSink);

  if (writeFile && !filename.empty()) {
    Ref<sinks::basic_file_sink_mt> fileSink =
        MakeRef<spdlog::sinks::basic_file_sink_mt>(filename, true);

    fileSink->set_pattern(pattern);

    this->_sinks.emplace_back(fileSink);
  }
}

Ref<Logger> DefaultLoggerFactoryImpl::construct(const std::string &name) {
  return MakeRef<DefaultLoggerImpl>(name, this->_sinks, this->_logLevel);
}

const std::string &DefaultLoggerFactoryImpl::getImplName() const noexcept {
  return DefaultLoggerFactoryImpl::_implName;
}

}  // namespace vanadium
