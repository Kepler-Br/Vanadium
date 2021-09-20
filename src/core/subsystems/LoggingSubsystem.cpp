#include "LoggingSubsystem.h"

#include <utility>

#include "core/Log.h"

namespace vanadium {

LoggingSubsystem::LoggingSubsystem(spdlog::level::level_enum level,
                                   bool writeFile, std::string filename)
    : Subsystem("Logging"),
      _level(level),
      _writeFile(writeFile),
      _filename(std::move(filename)) {}

void LoggingSubsystem::init() {
  Log::init(this->_level, this->_writeFile, this->_filename);
}

void LoggingSubsystem::shutdown() {
  // noop.
}

}  // namespace vanadium
