#include "DefaultLoggerImpl.h"

#include "SpdLogLevelConvertor.h"

namespace vanadium {

DefaultLoggerImpl::DefaultLoggerImpl(Ref<spdlog::logger> logger)
    : _logger(std::move(logger)) {}

void DefaultLoggerImpl::setLevel(LogLevel logLevel) {
  spdlog::level::level_enum level = toSpdLogLevel(logLevel);

  this->_logger->set_level(level);
}

LogLevel DefaultLoggerImpl::getLevel() {
  return fromSpdLogLevel(this->_logger->level());
}

bool DefaultLoggerImpl::shouldLog(LogLevel logLevel) {
  if (this->getLevel() > logLevel) {
    return false;
  } else {
    return true;
  }
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
