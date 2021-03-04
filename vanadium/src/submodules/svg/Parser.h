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
    static std::unordered_map<std::string, std::string> getRawPaths(tinyxml2::XMLDocument &xmlDocument);
    static std::vector<Commands::Command *> parseStringCommands(const std::string &commands);

//    static std::unordered_map<std::string, std::string> readSvgPaths(const std::string &source);
//    static std::vector<Commands::Command *> parseCommands(const std::string &rawCommands);

    static Commands::CoordinateType charToCoordinateType(char command);
    static Commands::Type charToCommandType(char command);
    static bool isCommand(char command);
    static Commands::Move *parseMove(char commandChar, std::stringstream &ss);
    static Commands::Line *parseLine(char commandChar, std::stringstream &ss);
    static Commands::HLine *parseHLine(char commandChar, std::stringstream &ss);
    static Commands::VLine *parseVLine(char commandChar, std::stringstream &ss);
    static Commands::ClosePath *parseClosePath(char commandChar, std::stringstream &ss);
    static Commands::Cubic *parseCubic(char commandChar, std::stringstream &ss);
    static Commands::Quadratic *parseQuadratic(char commandChar, std::stringstream &ss);
    static Commands::CubicConnected *parseCubicConnected(char commandChar, std::stringstream &ss);
    static Commands::QuadraticConnected *parseQuadraticConnected(char commandChar, std::stringstream &ss);

public:
    Parser() = delete;

//    static std::vector<Ref<Path>> parse(const std::string &source);
    static Ref<Document> parse(const std::string &source);
};

}

}

#endif //VANADIUM_SVG_PARSER_H
