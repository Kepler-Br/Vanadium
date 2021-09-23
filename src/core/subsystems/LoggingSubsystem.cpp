#include "LoggingSubsystem.h"

#include <utility>

#include "core/Log.h"
#include "core/application/ApplicationProperties.h"
#include "core/interfaces/Application.h"

namespace vanadium {

LoggingSubsystem::LoggingSubsystem()
    : _name("logging"), _initializationStage(0) {}

LoggingSubsystem::LoggingSubsystem(std::string name,
                                   std::size_t initializationStage)
    : _name(std::move(name)), _initializationStage(initializationStage) {}

void LoggingSubsystem::initialize(EngineEndApplication &application) {
  auto &props = application.getProperties();

  Log::init(props.getLogLevel(), props.getWriteLogToDisc(), props.getLogPath());

  this->_initialized = true;
}
void LoggingSubsystem::deinitialize() {
  // noop.
}

const std::string &LoggingSubsystem::getName() const noexcept {
  return this->_name;
}

std::size_t LoggingSubsystem::getInitializationStage()
    const noexcept {
  return this->_initializationStage;
}

bool LoggingSubsystem::isInitialized() const noexcept {
  return this->_initialized;
}

}  // namespace vanadium
