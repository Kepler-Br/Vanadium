#include "vanadium/core/Log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace vanadium {

std::shared_ptr<spdlog::logger> Log::_engineLogger;
std::shared_ptr<spdlog::logger> Log::_userLogger;

void Log::init(spdlog::level::level_enum level, bool writeFile,
               const std::string &filename) {
  std::vector<spdlog::sink_ptr> logSinks;
#if defined(VANADIUM_PLATFORM_LINUX) || defined(VANADIUM_PLATFORM_MACOS)
  Ref<spdlog::sinks::ansicolor_stdout_sink_mt> colorSink =
      MakeRef<spdlog::sinks::ansicolor_stdout_sink_mt>();
#elif VANADIUM_PLATFORM_WINDOWS
  Ref<spdlog::sinks::wincolor_stdout_sink_mt> colorSink =
      MakeRef<spdlog::sinks::wincolor_stdout_sink_mt>();
#endif
  colorSink->set_pattern("[%T] [%l] %n: %v");
  logSinks.emplace_back(colorSink);
  if (writeFile) {
    Ref<spdlog::sinks::basic_file_sink_mt> fileSink =
        MakeRef<spdlog::sinks::basic_file_sink_mt>(filename, true);
    fileSink->set_pattern("[%T] [%l] %n: %v");
    logSinks.emplace_back(fileSink);
  }

  Log::_engineLogger =
      MakeRef<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));
  spdlog::register_logger(Log::_engineLogger);
  Log::_engineLogger->set_level(level);
  Log::_engineLogger->flush_on(level);

  Log::_userLogger =
      MakeRef<spdlog::logger>("USER", begin(logSinks), end(logSinks));
  spdlog::register_logger(Log::_userLogger);
  Log::_userLogger->set_level(level);
  Log::_userLogger->flush_on(level);
}

}  // namespace vanadium
