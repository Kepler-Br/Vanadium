#include "core/Log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace vanadium {

std::shared_ptr<spdlog::logger> Log::_engineLogger;
std::shared_ptr<spdlog::logger> Log::_userLogger;

void Log::init(spdlog::level::level_enum level) {
  std::vector<spdlog::sink_ptr> logSinks;
  logSinks.emplace_back(
      std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
  logSinks.emplace_back(
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log.log", true));

  //    logSinks[0]->set_pattern("%^[%T] %n: %v%$");
  logSinks[0]->set_pattern("[%T] [%l] %n: %v");
  logSinks[1]->set_pattern("[%T] [%l] %n: %v");

  Log::_engineLogger = std::make_shared<spdlog::logger>(
      "ENGINE", begin(logSinks), end(logSinks));
  spdlog::register_logger(Log::_engineLogger);
  Log::_engineLogger->set_level(level);
  Log::_engineLogger->flush_on(level);

  Log::_userLogger =
      std::make_shared<spdlog::logger>("USER", begin(logSinks), end(logSinks));
  spdlog::register_logger(Log::_userLogger);
  Log::_userLogger->set_level(level);
  Log::_userLogger->flush_on(level);
}

}  // namespace vanadium
