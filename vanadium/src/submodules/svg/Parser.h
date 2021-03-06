#ifndef VANADIUM_SVG_PARSER_H
#define VANADIUM_SVG_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../core/Types.h"
#include "Document.h"
#include "Commands.h"
#include "Types.h"
#include "Path.h"

namespace tinyxml2 {class XMLDocument;}

namespace Vanadium
{

namespace Svg
{


class Parser
{
private:
    static const std::unordered_map<char, Commands::CoordinateType> commandCharToCoordinateTypeMap;
    static const std::unordered_map<char, Commands::Type> commandCharToTypeMap;
    static const std::unordered_set<char> commandChars;

    static glm::vec2 getDocumentDimensions(tinyxml2::XMLDocument &xmlDocument);
    static std::string getDocumentName(tinyxml2::XMLDocument &xmlDocument);
    static std::unordered_map<std::string, std::vector<std::string>> getRawLayers(tinyxml2::XMLDocument &xmlDocument);
    static std::vector<Commands::Command *> parseStringCommands(const std::string &commandsString);

//    static std::unordered_map<std::string, std::string> readSvgPaths(const std::string &source);
//    static std::vector<Commands::Command *> parseCommands(const std::string &rawCommands);

    static const char *skipDouble(const char *str);
    static bool isDouble(char ch);
    static const char *skipWhitespace(const char *str);
    static bool parseVec2(const char **str, glm::vec2 &val);
    static Commands::CoordinateType charToCoordinateType(char command);
    static Commands::Type charToCommandType(char command);
    static bool isCommand(char command);
    static Commands::Move *parseMove(const char **cString);
    static Commands::Line *parseLine(const char **cString);
    static Commands::HLine *parseHLine(const char **cString);
    static Commands::VLine *parseVLine(const char **cString);
    static Commands::ClosePath *parseClosePath(const char **cString);
    static Commands::Cubic *parseCubic(const char **cString);
//    static Commands::Quadratic *parseQuadratic(char commandChar, std::stringstream &ss);
    static Commands::CubicConnected *parseCubicConnected(const char **cString);
//    static Commands::QuadraticConnected *parseQuadraticConnected(char commandChar, std::stringstream &ss);

public:
    Parser() = delete;

//    static std::vector<Ref<Path>> parse(const std::string &source);
    static Document *parse(const std::string &source);
};

}

}

#endif //VANADIUM_SVG_PARSER_H
