#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Vanadium
{

std::shared_ptr<spdlog::logger> Log::engineLogger;
std::shared_ptr<spdlog::logger> Log::userLogger;

void Log::init(spdlog::level::level_enum level)
{
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Vanadium.log", true));

    logSinks[0]->set_pattern("%^[%T] %n: %v%$");
    logSinks[1]->set_pattern("[%T] [%l] %n: %v");

    Log::engineLogger = std::make_shared<spdlog::logger>("HAZEL", begin(logSinks), end(logSinks));
    spdlog::register_logger(Log::engineLogger);
    Log::engineLogger->set_level(level);
    Log::engineLogger->flush_on(level);

    Log::userLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
    spdlog::register_logger(Log::userLogger);
    Log::userLogger->set_level(level);
    Log::userLogger->flush_on(level);
}

}