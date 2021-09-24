#pragma once

#include <string>
#include <vector>

#include "core/Log.h"
#include "core/types/window/WindowProperties.h"
#include "graphics/RendererApiEnum.h"

namespace vanadium {

class ApplicationProperties {
 private:
  WindowProperties _windowProperties;
  std::vector<std::string> _programArguments;
  bool _shouldWriteLogsToDisk = true;
  std::string _logsPath = "logs.txt";
  LogLevel _logsLevel = LogLevel::trace;
  std::vector<RendererApi> _renderApiPriority{};

  void convertArguments(int argc, char **argv) noexcept;

 public:
  ApplicationProperties() noexcept = default;

  // Getters
  [[nodiscard]] const WindowProperties &getWindowProperties() const noexcept;
  [[nodiscard]] const std::vector<RendererApi> &getRenderApiPriority()
      const noexcept;
  [[nodiscard]] const std::vector<std::string> &getArguments() const noexcept;
  [[nodiscard]] bool getWriteLogToDisc() const noexcept;
  [[nodiscard]] const std::string &getLogPath() const noexcept;
  [[nodiscard]] LogLevel getLogLevel() const noexcept;

  // Setters.
  ApplicationProperties &withWriteLogsToDisc(bool shouldWrite) noexcept;
  ApplicationProperties &withArguments(int argc, char **argv) noexcept;
  ApplicationProperties &withArguments(std::vector<std::string> args) noexcept;
  ApplicationProperties &withLogPath(std::string logsPath) noexcept;
  ApplicationProperties &withLogLevel(LogLevel logsLevel) noexcept;
  ApplicationProperties &withWindow(const WindowProperties &winProps) noexcept;
  ApplicationProperties &withRenderApiPriority(
      std::vector<RendererApi> renderPriorityApi) noexcept;
};

}  // namespace vanadium
