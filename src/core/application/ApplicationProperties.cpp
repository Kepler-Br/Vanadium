#include "ApplicationProperties.h"

namespace vanadium {

void ApplicationProperties::convertArguments(int argc, char **argv) noexcept {
  if (argv != nullptr) {
    this->_programArguments.reserve((size_t)argc);
    for (int i = 0; i < argc; i++) {
      this->_programArguments.emplace_back(argv[i]);
    }
  }
}

ApplicationProperties::ApplicationProperties(int argc, char **argv) noexcept {
  this->convertArguments(argc, argv);
}

const WindowProperties &ApplicationProperties::getWindowProperties()
    const noexcept {
  return this->_windowProperties;
}

const std::vector<std::string> &ApplicationProperties::getArguments()
    const noexcept {
  return this->_programArguments;
}

bool ApplicationProperties::getWriteLogToDisc() const noexcept {
  return this->_shouldWriteLogsToDisk;
}

const std::string &ApplicationProperties::getLogPath() const noexcept {
  return this->_logsPath;
}

LogLevel ApplicationProperties::getLogLevel() const noexcept {
  return this->_logsLevel;
}

ApplicationProperties &ApplicationProperties::withWriteLogsToDisc(
    bool shouldWrite) noexcept {
  this->_shouldWriteLogsToDisk = shouldWrite;

  return *this;
}
ApplicationProperties &ApplicationProperties::withLogPath(
    std::string logsPath) noexcept {
  this->_logsPath = std::move(logsPath);

  return *this;
}
ApplicationProperties &ApplicationProperties::withLogLevel(
    LogLevel logsLevel) noexcept {
  this->_logsLevel = logsLevel;

  return *this;
}
ApplicationProperties &ApplicationProperties::withWindow(
    WindowProperties &winProps) noexcept {
  this->_windowProperties = winProps;

  return *this;
}

}  // namespace vanadium
