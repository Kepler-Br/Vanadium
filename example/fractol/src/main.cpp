#include <vanadium/Vanadium.h>

#include "AppInitHook.h"

std::string computeMethodName(const std::string& function,
                              const std::string& prettyFunction);

#define __COMPACT_PRETTY_FUNCTION__                    \
  computeMethodName(__FUNCTION__, __PRETTY_FUNCTION__) \
      .c_str()  // c_str() is optional

std::string computeMethodName(const std::string& function,
                              const std::string& prettyFunction) {
  // If the input is a constructor, it gets the beginning of the class name, not
  // of the method. That's why later on we have to search for the first
  // parenthesys
  size_t locFunName = prettyFunction.find(function);
  size_t begin = prettyFunction.rfind(' ', locFunName) + 1;
  // Adding function.length() make this faster and also allows to handle
  // operator parenthesys!
  size_t end = prettyFunction.find('(', locFunName + function.length());
  if (prettyFunction[end + 1] == ')') {
    return (prettyFunction.substr(begin, end - begin) + "()");
  } else {
    return (prettyFunction.substr(begin, end - begin) + "(...)");
  }
}

//constexpr std::string_view computeMethodNameConstexpr(
//    const std::string_view& function, const std::string_view& prettyFunction) {
//  // If the input is a constructor, it gets the beginning of the class name, not
//  // of the method. That's why later on we have to search for the first
//  // parenthesys
//  size_t locFunName = prettyFunction.find(function);
//  size_t begin = prettyFunction.rfind(' ', locFunName) + 1;
//  // Adding function.length() make this faster and also allows to handle
//  // operator parenthesys!
//  size_t end = prettyFunction.find('(', locFunName + function.length());
//  if (prettyFunction[end + 1] == ')') {
//    return (prettyFunction.substr(begin, end - begin) + "()");
//  } else {
//    return (prettyFunction.substr(begin, end - begin) + "(...)");
//  }
//}

class Test {
 public:
  void print(char* someArg) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    std::cout << __COMPACT_PRETTY_FUNCTION__ << std::endl;
  }
};

int main(int argc, char** argv) {
  using namespace vanadium;

  Ref<AppInitHook> appInitHook = MakeRef<AppInitHook>();
  Test test;

  test.print(nullptr);

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
