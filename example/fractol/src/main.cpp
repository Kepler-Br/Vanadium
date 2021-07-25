#include <Vanadium.h>

#include "EntryPoint.h"
#include "states/MainState.h"

int main(int argc, char **argv) {
  using namespace vanadium;

  auto winProps = WindowProperties()
                      .withGeometry({900, 800})
                      .withTitle("Vanadium:: Fract'ol")
                      .withType(WindowType::Resizable);
  auto appProps = ApplicationProperties(argc, argv)
                      .withWindow(winProps)
                      .withLogLevel(LogLevel::trace)
                      .withWriteLogsToDisc(false);

  auto app = EntryPoint();
  app.init(appProps);
  app.pushState<MainState>("Main state");
  app.run();
  return 0;
}
