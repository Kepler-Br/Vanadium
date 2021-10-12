//#include <vanadium/Vanadium.h>

#include <vanadium/core/interfaces/Application.h>
//#include <vanadium/core/interfaces/FactoryContainer.h>
//#include <vanadium/core/interfaces/MainLoop.h>
//#include <vanadium/core/interfaces/constructed/EventProvider.h>
//#include <vanadium/core/interfaces/constructed/StateStack.h>
#pragma region implementations
//#include <vanadium/core/application/ApplicationImpl.h>
//#include <vanadium/core/application/FactoryContainerImpl.h>
#include <vanadium/core/application/MainLoopImpl.h>
//#include <vanadium/core/application/StateStackImpl.h>
//#include <vanadium/platform/sdl/SdlEventProviderImpl.h>
#pragma endregion

#include <vanadium/core/types/Reference.h>

#include "AppInitHook.h"
#include "DefaultInjector.h"
#include "states/TestState.h"

using vanadium::Ref;

int main(int argc, char** argv) {
  using namespace vanadium;

  auto winProps = WindowProperties()
                      .withGeometry({900, 800})
                      .withTitle("Vanadium:: Fract'ol")
                      .withType(WindowType::Resizable);
  auto appProps = ApplicationProperties()
                      .withWindow(winProps)
                      .withLogLevel(LogLevel::Trace)
                      .withArguments(argc, argv)
                      .withRenderApiPriority({RendererApi::Vulkan});

  for(auto &arg : appProps.getArguments()) {
    std::cout << "Arg: " << arg << std::endl;
  }
  std::cout << "Size: " << appProps.getArguments().size() << std::endl;

  auto injector = getInjector(appProps);
  auto application = injector.template create<Ref<EngineEndApplication>>();
  auto appInitHook = injector.template create<Ref<AppInitHook>>();

  application->setInitializationHook(appInitHook);
  application->setProperties(appProps);
  application->initialize();
  application->pushState<TestState>();
  application->run();
  return 0;
}
