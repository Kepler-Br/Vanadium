#ifndef VANADIUM_SVG_PARSER_H
#define VANADIUM_SVG_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../core/Types.h"
#include "Types.h"
#include "Commands.h"
#include "Path.h"

namespace Vanadium
{

namespace Svg
{

class Parser
{
private:
    std::unordered_map<std::string, std::string> svgRawPaths;

    void readSvgPaths(const std::string &source);
    void parseCommands(const std::string &rawCommands);

    static const std::unordered_map<char, Commands::CoordinateType> commandCharToCoordinateTypeMap;
    static const std::unordered_map<char, Commands::Type> commandCharToTypeMap;
    static const std::unordered_set<char> commandChars;

    static Commands::CoordinateType charToCoordinateType(char command);
    static Commands::Type charToCommandType(char command);
    static bool isCommand(char command);
    static Commands::Cubic *parseCubic(std::stringstream &ss);
//    static const char *skipWhiteSpace(const char *str);
//    static const char *skipNotCommands(const char *str);

    std::vector<Commands::Command *> commands;

public:
    Parser(const std::string &source);

};

}

}

#endif //VANADIUM_SVG_PARSER_H
