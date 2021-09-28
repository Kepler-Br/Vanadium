//#include <vanadium/Vanadium.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vanadium/core/application/FactoryContainerImpl.h>
#include <vanadium/core/interfaces/FactoryContainer.h>
#include <vanadium/core/interfaces/constructed/factories/LoggerFactory.h>
#include <vanadium/platform/default/factories/DefaultLoggerFactoryImpl.h>

#include "AppInitHook.h"

int main(int argc, char** argv) {
  using namespace vanadium;

  Ref<AppInitHook> appInitHook = MakeRef<AppInitHook>();

  Ref<FactoryContainer> factoryContainer = MakeRef<FactoryContainerImpl>();

  factoryContainer->registerFactory<DefaultLoggerFactoryImpl>(
      LogLevel::Trace);

  Ref<LoggerFactory> loggerFactory =
      factoryContainer->getFactory<LoggerFactory>();
  Ref<Logger> logger = loggerFactory->construct("main");

  logger->log(LogLevel::Warning, "Hi, {}!", "Igor");
  logger->trace("This is {} message", "trace");
  logger->debug("This is {} message", "debug");
  logger->info("This is {} message", "info");
  logger->warn("This is {} message", "warn");
  logger->error("This is {} message", "error");
  logger->critical("This is {} message", "critical");

//  virtual void trace(const std::string &message) = 0;
//  virtual void debug(const std::string &message) = 0;
//  virtual void info(const std::string &message) = 0;
//  virtual void warn(const std::string &message) = 0;
//  virtual void error(const std::string &message) = 0;
//  virtual void critical(const std::string &message) = 0;

//  auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
//  auto colorLogger = std::make_shared<spdlog::logger>("my_logger", sink);
//  colorLogger->warn("Warn");
//  colorLogger->log("Warn");
//  colorLogger->debug("Warn");
//  colorLogger->critical("Critical");
//  colorLogger->error("Error");

  //  auto winProps = WindowProperties()
  //                      .withGeometry({900, 800})
  //                      .withTitle("Vanadium:: Fract'ol")
  //                      .withType(WindowType::Resizable);
  //  auto appProps = ApplicationProperties(argc, argv)
  //                      .withWindow(winProps)
  //                      .withLogLevel(LogLevel::trace)
  //                      .withWriteLogsToDisc(false)
  //                      .withRenderApiPriority({RendererApi::Vulkan});
  //
  //  auto app = EntryPoint();
  //  app.init(appProps);
  //  app.pushState<MainState>("Main state");
  //  app.run();
  return 0;
}
