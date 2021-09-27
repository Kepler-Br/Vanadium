#include "DefaultLoggerImpl.h"

#include "ToSpdLogLevel.h"

namespace vanadium {

DefaultLoggerImpl::DefaultLoggerImpl(const std::string& name,
                                     std::vector<spdlog::sink_ptr>& sinks,
                                     LogLevel logLevel) {
  this->_logger = spdlog::get(name);

  if (this->_logger == nullptr) {
    this->_logger = MakeRef<spdlog::logger>(name, begin(sinks), end(sinks));
  }

  spdlog::register_logger(this->_logger);

  spdlog::level::level_enum level =
      toSpdLogLevel(logLevel);

  this->_logger->set_level(level);
  this->_logger->flush_on(level);
}

void DefaultLoggerImpl::setLevel(LogLevel logLevel) {
  spdlog::level::level_enum level =
      toSpdLogLevel(logLevel);

  this->_logger->set_level(level);
  this->_logger->flush_on(level);
}

LogLevel DefaultLoggerImpl::getLevel() {
  return fromSpdLogLevel(this->_logger->level());
}

void DefaultLoggerImpl::log(LogLevel level, const std::string& message) {
  this->_logger->log(toSpdLogLevel(level), message);
}

void DefaultLoggerImpl::debug(const std::string& message) {
  this->_logger->debug(message);
}

void DefaultLoggerImpl::trace(const std::string& message) {
  this->_logger->trace(message);
}

void DefaultLoggerImpl::info(const std::string& message) {
  this->_logger->info(message);
}

void DefaultLoggerImpl::warn(const std::string& message) {
  this->_logger->warn(message);
}

void DefaultLoggerImpl::error(const std::string& message) {
  this->_logger->error(message);
}
void DefaultLoggerImpl::critical(const std::string& message) {
  this->_logger->critical(message);
}

}  // namespace vanadium
