#pragma once

#include <string>
#include <vector>

#include "vanadium/core/types/LogLevel.h"
#include "vanadium/core/types/window/WindowProperties.h"
#include "vanadium/graphics/RendererApiEnum.h"

namespace vanadium {

class ApplicationProperties {
 private:
  WindowProperties _windowProperties;
  std::vector<std::string> _programArguments;
  std::string _logsPath;
  LogLevel _logsLevel = LogLevel::Trace;
  std::vector<RendererApi> _renderApiPriority{};

  void convertArguments(int argc, char **argv) noexcept;

 public:
  ApplicationProperties() noexcept = default;

  // Getters
  [[nodiscard]] const WindowProperties &getWindowProperties() const noexcept;
  [[nodiscard]] const std::vector<RendererApi> &getRenderApiPriority()
      const noexcept;
  [[nodiscard]] const std::vector<std::string> &getArguments() const noexcept;
  [[nodiscard]] const std::string &getLogPath() const noexcept;
  [[nodiscard]] LogLevel getLogLevel() const noexcept;

  // Setters.
  ApplicationProperties &withArguments(int argc, char **argv) noexcept;
  ApplicationProperties &withArguments(std::vector<std::string> args) noexcept;
  ApplicationProperties &withLogPath(std::string logsPath) noexcept;
  ApplicationProperties &withLogLevel(LogLevel logsLevel) noexcept;
  ApplicationProperties &withWindow(const WindowProperties &winProps) noexcept;
  ApplicationProperties &withRenderApiPriority(
      std::vector<RendererApi> renderPriorityApi) noexcept;
};

}  // namespace vanadium
