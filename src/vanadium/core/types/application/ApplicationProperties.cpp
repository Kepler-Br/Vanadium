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

const WindowProperties &ApplicationProperties::getWindowProperties()
    const noexcept {
  return this->_windowProperties;
}

const std::vector<RendererApi> &ApplicationProperties::getRenderApiPriority()
    const noexcept {
  return this->_renderApiPriority;
}

const std::vector<std::string> &ApplicationProperties::getArguments()
    const noexcept {
  return this->_programArguments;
}

const std::string &ApplicationProperties::getLogPath() const noexcept {
  return this->_logsPath;
}

LogLevel ApplicationProperties::getLogLevel() const noexcept {
  return this->_logsLevel;
}

ApplicationProperties &ApplicationProperties::withArguments(
    int argc, char **argv) noexcept {
  this->convertArguments(argc, argv);

  return *this;
}

ApplicationProperties &ApplicationProperties::withArguments(
    std::vector<std::string> args) noexcept {
  this->_programArguments = std::move(args);

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
    const WindowProperties &winProps) noexcept {
  this->_windowProperties = winProps;

  return *this;
}

ApplicationProperties &ApplicationProperties::withRenderApiPriority(
    std::vector<RendererApi> renderPriorityApi) noexcept {
  this->_renderApiPriority = std::move(renderPriorityApi);

  return *this;
}

}  // namespace vanadium
