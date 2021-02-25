#include "include/vanadium/Vanadium.h"
#include "states/CustomState.h"
#warning "Implement state commands."
#warning "Add OnWindowStopResizingEvent."
#warning "Add vendor information on start."
#warning "Deal with GLEW compilation."
#include <tinyxml2.h>
#include <iostream>

std::string getShaderSource(tinyxml2::XMLElement *node, Shader::Type type)
{
    const std::string &typeString = Shader::typeToString(type);

    if (node == nullptr)
        throw ShaderAssetParsingError("Cannot get shader source when XMLElement == nullptr.");
    tinyxml2::XMLElement *sourceElement = node->FirstChildElement(typeString.c_str());
    if (sourceElement == nullptr)
        throw ShaderAssetParsingError("Shader type not found in shader asset: " + typeString + ".");
    return sourceElement->GetText();
}

tinyxml2::XMLElement *getRenderApiSourceNode(tinyxml2::XMLElement *element, RenderApi::Api api)
{
    const std::string &apiString = RenderApi::apiToString(api);

    element = element->FirstChildElement(apiString.c_str());
    if (element == nullptr)
        throw ShaderAssetParsingError("Shader asset has no shaders for render API: " + apiString);
    return element;
}

int main(int argc, char** argv)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "shader.xml" );
    tinyxml2::XMLElement *apiSourceNode = getRenderApiSourceNode(doc.RootElement(), RenderApi::Api::OpenGL);

    for (tinyxml2::XMLElement* child = apiSourceNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        std::cout << child->Value() << std::endl;
        std::cout << child->GetText() << std::endl;
    }

//    auto hasher = std::hash<std::string>();
//    std::vector<std::string> strings({"Vertex", "Pixel", "Geometry", "Compute", "TesselationControl", "TesselationEval"});
//    for (auto str : strings)
//    {
//        std::cout << str << " is " << hashString(str) << std::endl;
//    }

//    constexpr size_t test = std::hash<std::string>()("123");

    using namespace Vanadium;
    // No tag-based init for structures in C++ :'(.
    // Todo: refactor me.
    Window::Specification winSpecs;
    winSpecs.width = 800;
    winSpecs.height = 600;
    winSpecs.title = "Oh, my~";
    Application::Specification appSpecs;
    appSpecs.winSpecs = winSpecs;
    appSpecs.argc = argc;
    appSpecs.argv = argv;
//    auto *app = new Application(appSpecs);
//    app->forcePushArgumentlessState<CustomState>("Custom state");
//    app->run();
//    delete app;
    return 0;
}
