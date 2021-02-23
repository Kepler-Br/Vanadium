#include "include/vanadium/Vanadium.h"
//#include <yaml-cpp/yaml.h>
//#include <iostream>
//#include <string>
#error "You forgot to use smart pointers instead of raw ones."

int main(int argc, char** argv)
{
    using namespace Vanadium;

    auto *app = new Application("Oh my~", 800, 600, nullptr);
    app->run();
    delete app;
//    YAML::Node config = YAML::LoadFile("shader.yaml")["OpenGL"];
//
//    for (auto node : config)
//    {
//        std::cout << node.first.as<std::string>() << std::endl;
//    }
//    std::cout << (config["OpenGL"] ? true : false) << std::endl;
    return 0;
}
