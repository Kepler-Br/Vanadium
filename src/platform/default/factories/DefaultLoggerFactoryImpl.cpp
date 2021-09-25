#include "DefaultLoggerFactoryImpl.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "platform/default/DefaultLoggerImpl.h"

namespace vanadium {

DefaultLoggerFactoryImpl::DefaultLoggerFactoryImpl(const std::string& filename,
                                                   bool writeFile,
                                                   LogLevel logLevel)
    : _logLevel(logLevel) {
  using namespace spdlog;
  const std::string pattern = "[%T] [%l] %n: %v";

  Ref<sinks::ansicolor_stdout_sink_mt> colorSink =
      MakeRef<spdlog::sinks::ansicolor_stdout_sink_mt>();

  colorSink->set_pattern(pattern);

  this->_sinks.emplace_back(colorSink);

  if (writeFile) {
    Ref<sinks::basic_file_sink_mt> fileSink =
        MakeRef<spdlog::sinks::basic_file_sink_mt>(filename, true);

    fileSink->set_pattern(pattern);

    this->_sinks.emplace_back(fileSink);
  }
}

Ref<Logger> DefaultLoggerFactoryImpl::construct(const std::string& name) {
  return MakeRef<DefaultLoggerImpl>(name, this->_sinks, this->_logLevel);
}

}  // namespace vanadium
