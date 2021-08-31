#pragma once

#include <string>
#include <vector>

#include "graphics/RendererApiEnum.h"

#include "core/Log.h"
#include "core/Window.h"

namespace vanadium {

class ApplicationProperties {
 protected:
  WindowProperties _windowProperties;
  std::vector<std::string> _programArguments;
  bool _shouldWriteLogsToDisk = true;
  std::string _logsPath = "logs.txt";
  LogLevel _logsLevel = LogLevel::trace;
  std::vector<RendererApi> _renderApiPriority{};

  void convertArguments(int argc, char **argv) noexcept;

 public:
  ApplicationProperties(int argc, char **argv) noexcept;

  // Getters
  [[nodiscard]] const WindowProperties &getWindowProperties() const noexcept;
  [[nodiscard]] const std::vector<std::string> &getArguments() const noexcept;
  [[nodiscard]] bool getWriteLogToDisc() const noexcept;
  [[nodiscard]] const std::string &getLogPath() const noexcept;
  [[nodiscard]] LogLevel getLogLevel() const noexcept;

  // Setters.
  ApplicationProperties &withWriteLogsToDisc(bool shouldWrite) noexcept;
  ApplicationProperties &withLogPath(std::string logsPath) noexcept;
  ApplicationProperties &withLogLevel(LogLevel logsLevel) noexcept;
  ApplicationProperties &withWindow(const WindowProperties &winProps) noexcept;
  ApplicationProperties &withRenderApiPriority(
      std::initializer_list<RendererApi>
          renderPriorityApi) noexcept;
};

}  // namespace vanadium
