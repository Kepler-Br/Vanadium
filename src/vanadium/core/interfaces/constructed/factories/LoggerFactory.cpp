#include "LoggerFactory.h"

namespace vanadium {

std::string LoggerFactory::_name = "LoggerFactory";

const std::string &LoggerFactory::getName() const noexcept {
  return LoggerFactory::_name;
}

const std::string &LoggerFactory::getFactoryName() noexcept {
  return LoggerFactory::_name;
}

}  // namespace vanadium
