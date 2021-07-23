#include <Vanadium.h>

#include "EntryPoint.h"
#include "states/MainState.h"

int main(int argc, char **argv) {
  using namespace vanadium;

  WindowProperties winProps = WindowProperties({900, 800})
                                  .withTitle("Vanadium:: example")
                                  .withType(WindowType::Resizable);
  ApplicationProperties appProps(winProps, argc, argv);

  auto app = MakeUnique<EntryPoint>();
  app->init(appProps);
  app->pushState<MainState>("Main state");
  app->run();
  return 0;
}
