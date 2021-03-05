#include "Parser.h"

#include <utility>
#include <tinyxml2.h>
#include <sstream>
#include <iostream>
#include <cstring>
#include "../../core/Tools.h"

namespace Vanadium
{

namespace Svg
{

const std::unordered_map<char, Commands::CoordinateType> Parser::commandCharToCoordinateTypeMap = {
        {'m', Commands::CoordinateType::Relative},
        {'M', Commands::CoordinateType::Absolute},
        {'l', Commands::CoordinateType::Relative},
        {'L', Commands::CoordinateType::Absolute},
        {'h', Commands::CoordinateType::Relative},
        {'H', Commands::CoordinateType::Absolute},
        {'v', Commands::CoordinateType::Relative},
        {'V', Commands::CoordinateType::Absolute},
        {'q', Commands::CoordinateType::Relative},
        {'Q', Commands::CoordinateType::Absolute},
        {'c', Commands::CoordinateType::Relative},
        {'C', Commands::CoordinateType::Absolute},
        {'s', Commands::CoordinateType::Relative},
        {'S', Commands::CoordinateType::Absolute},
        {'t', Commands::CoordinateType::Relative},
        {'T', Commands::CoordinateType::Absolute},
};

const std::unordered_map<char, Commands::Type> Parser::commandCharToTypeMap = {
        {'m', Commands::Type::Move},
        {'M', Commands::Type::Move},
        {'l', Commands::Type::Line},
        {'L', Commands::Type::Line},
        {'h', Commands::Type::HorizontalLine},
        {'H', Commands::Type::HorizontalLine},
        {'v', Commands::Type::VerticalLine},
        {'V', Commands::Type::VerticalLine},
        {'z', Commands::Type::ClosePath},
        {'Z', Commands::Type::ClosePath},
        {'c', Commands::Type::Cubic},
        {'C', Commands::Type::Cubic},
        {'Q', Commands::Type::Quadratic},
        {'q', Commands::Type::Quadratic},
        {'s', Commands::Type::CubicConnected},
        {'S', Commands::Type::CubicConnected},
        {'t', Commands::Type::QuadraticConnected},
        {'T', Commands::Type::QuadraticConnected},
};

const std::unordered_set<char> Parser::commandChars = {
        'm',
        'M',
        'l',
        'L',
        'h',
        'H',
        'v',
        'V',
        'z',
        'Z',
        'c',
        'C',
        'q',
        'Q',
        's',
        'S',
        't',
        'T',
};

glm::vec2 Parser::getDocumentDimensions(tinyxml2::XMLDocument &xmlDocument)
{
    std::stringstream ss;
    glm::vec2 dimensions;
    const char *width = xmlDocument.RootElement()->Attribute("width");
    const char *height = xmlDocument.RootElement()->Attribute("height");

    if (width == nullptr)
        dimensions.x = 0;
    else
    {
        float val;
        ss = std::stringstream (width);
        ss >> val;
        if (ss.fail())
            dimensions.x = 0;
        else
            dimensions.x = val;
    }
    if (height == nullptr)
        dimensions.y = 0;
    else
    {
        float val;
        ss = std::stringstream (height);
        ss >> val;
        if (ss.fail())
            dimensions.y = 0;
        else
            dimensions.y = val;
    }
    if (dimensions.x == 0.0f && dimensions.y == 0.0f)
    {
        const char *viewbox = xmlDocument.RootElement()->Attribute("viewBox");
        if (viewbox != nullptr)
        {
            ss = std::stringstream (viewbox);
            ss >> dimensions.x >> dimensions.x;
            ss >> dimensions.x >> dimensions.y;
            if (ss.fail())
                dimensions = {0.0f, 0.0f};
        }
    }
    return dimensions;
}
std::string Parser::getDocumentName(tinyxml2::XMLDocument &xmlDocument)
{
    const char *name = xmlDocument.RootElement()->Attribute("id");
    return std::string(name == nullptr ? "" : name);
}

std::unordered_map<std::string, std::string> Parser::getRawPaths(tinyxml2::XMLDocument &xmlDocument)
{
    std::unordered_map<std::string, std::string> rawPaths;

    tinyxml2::XMLElement *rootNode = xmlDocument.RootElement();
    tinyxml2::XMLElement *pathsNode = rootNode->FirstChildElement("g");
    if (pathsNode == nullptr)
    {
        pathsNode = rootNode;
        std::cout << "g node  not found! Assuming paths are inside root node." << std::endl;
//        return {};
    }
    for (tinyxml2::XMLElement* child = pathsNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        const char *nodeName = child->Value();
        if (std::strcmp(nodeName, "path") != 0)
            continue;
        const char *pathIdCString = child->Attribute("id");
        const std::string pathId = pathIdCString == nullptr ? Tools::randomString(10) : pathIdCString;
        const char *commandsCString = child->Attribute("d");
        const std::string commands = commandsCString == nullptr ? "" : commandsCString;
        if (commands.empty())
        {
            std::cout << "Command is empty!" << std::endl;
            continue;
        }
        rawPaths[pathId] = commands;
    }
    return rawPaths;
}

std::vector<Commands::Command *> Parser::parseStringCommands(const std::string &commands)
{
    std::stringstream ss(commands);
    std::vector<Commands::Command *> parsedCommands;
    while(!ss.eof())
    {
        char commandChar = '\0';
        ss >> commandChar;
        if (ss.eof() || ss.fail())
            break;
        if (!Parser::isCommand(commandChar))
            continue;
        Commands::Type commandType = charToCommandType(commandChar);
        Commands::Command *command;
        switch (commandType)
        {
            case Commands::Type::Cubic:
                command = Parser::parseCubic(commandChar, ss);
                break;
            case Commands::Type::Move:
                command = Parser::parseMove(commandChar, ss);
                break;
            case Commands::Type::Line:
                command = Parser::parseLine(commandChar, ss);
                break;
            case Commands::Type::HorizontalLine:
                command = Parser::parseHLine(commandChar, ss);
                break;
            case Commands::Type::VerticalLine:
                command = Parser::parseVLine(commandChar, ss);
                break;
            case Commands::Type::ClosePath:
                command = Parser::parseClosePath(commandChar, ss);
                break;
            case Commands::Type::Quadratic:
                command = Parser::parseQuadratic(commandChar, ss);
                break;
            case Commands::Type::CubicConnected:
                command = Parser::parseCubicConnected(commandChar, ss);
                break;
            case Commands::Type::QuadraticConnected:
                command = Parser::parseQuadraticConnected(commandChar, ss);
                break;
            case Commands::Type::Unknown:
            default:
                std::cout << "\"" << commandChar << "\"" <<  " command is not parsable yet!" << std::endl;
                continue;
        }
        if (command == nullptr)
        {
            std::cout << "Command \"" << commandChar << "\" is nullptr!" << std::endl;
            continue;
        }
        parsedCommands.push_back(command);
    }
    return parsedCommands;
}

Commands::CoordinateType Parser::charToCoordinateType(char command)
{
    auto found = Parser::commandCharToCoordinateTypeMap.find(command);
    if (found == Parser::commandCharToCoordinateTypeMap.end())
        return Commands::CoordinateType::Unknown;
    return found->second;
}

Commands::Type Parser::charToCommandType(char command)
{
    auto found = Parser::commandCharToTypeMap.find(command);
    if (found == Parser::commandCharToTypeMap.end())
        return Commands::Type::Unknown;
    return found->second;
}

bool Parser::isCommand(char command)
{
    auto found = Parser::commandChars.find(command);

    if (found == Parser::commandChars.end())
        return false;
    return true;
}

Commands::Cubic *Parser::parseCubic(char commandChar, std::stringstream &ss)
{
//    std::vector<glm::vec2> joints;
    CubicPoints points;
    Commands::CoordinateType coordinateType;
    float x, y;
    char comma;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> x >> comma >> y;
    if (ss.fail() || comma != ',')
        return nullptr;
    std::get<0>(points) = {x, y};
    ss >> x >> comma >> y;
    if (ss.fail() || comma != ',')
        return nullptr;
    std::get<1>(points) = {x, y};
    ss >> x >> comma >> y;
    if (ss.fail() || comma != ',')
        return nullptr;
    std::get<2>(points) = {x, y};
    return new Commands::Cubic(coordinateType, points);
}

Commands::Move *Parser::parseMove(char commandChar, std::stringstream &ss)
{
    float x, y;
    Commands::CoordinateType coordinateType;
    char comma;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> x >> comma >> y;
    if (ss.fail())
        return nullptr;
    if (comma != ',')
        return nullptr;
    return new Commands::Move(coordinateType, {x, y});
}

Commands::Line *Parser::parseLine(char commandChar, std::stringstream &ss)
{
    float x, y;
    Commands::CoordinateType coordinateType;
    char comma;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> x >> comma >> y;
    if (ss.fail())
        return nullptr;
    if (comma != ',')
        return nullptr;
    return new Commands::Line(coordinateType, {x, y});
}

Commands::HLine *Parser::parseHLine(char commandChar, std::stringstream &ss)
{
    float target;
    Commands::CoordinateType coordinateType;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;

    std::cout << "-----" << &ss.str().c_str()[ss.tellg()] << std::endl;
    ss >> target;

    if (ss.fail())
    {
        ss.clear();
        std::cout << "-----" << &ss.str().c_str()[ss.tellg()] << std::endl;
    std::string ohsthit;
    ss >> ohsthit;
    std::cout << "Oh shit: " << ohsthit << std::endl;
        return nullptr;
    }
    return new Commands::HLine(coordinateType, target);
}

Commands::VLine *Parser::parseVLine(char commandChar, std::stringstream &ss)
{
    float target;
    Commands::CoordinateType coordinateType;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> target;
    if (ss.fail())
        return nullptr;
    return new Commands::VLine(coordinateType, target);
}

Commands::ClosePath *Parser::parseClosePath(char commandChar, std::stringstream &ss)
{
    return new Commands::ClosePath();
}

Commands::Quadratic *Parser::parseQuadratic(char commandChar, std::stringstream &ss)
{
    QuadraticPoints points;
    Commands::CoordinateType coordinateType;
    float x, y;
    char comma;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> x >> comma >> y;
    if (ss.fail() || comma != ',')
        return nullptr;
    std::get<0>(points) = {x, y};
    ss >> x >> comma >> y;
    if (ss.fail() || comma != ',')
        return nullptr;
    std::get<1>(points) = {x, y};
    return new Commands::Quadratic(coordinateType, points);
}
Commands::CubicConnected *Parser::parseCubicConnected(char commandChar, std::stringstream &ss)
{
    std::pair<glm::vec2, glm::vec2> target;
    Commands::CoordinateType coordinateType;
    float x, y;
    char comma;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> x >> y;
    if (ss.fail())
        return nullptr;
    target.first = {x, y};
    ss >> comma;
    ss >> x >> y;
    if (comma != ',')
        return nullptr;
    if (ss.fail())
        return nullptr;
    target.second = {x, y};
    return new Commands::CubicConnected(coordinateType, target);
}

Commands::QuadraticConnected *Parser::parseQuadraticConnected(char commandChar, std::stringstream &ss)
{
    glm::vec2 target;
    Commands::CoordinateType coordinateType;
    float x, y;

    coordinateType = Parser::charToCoordinateType(commandChar);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    ss >> x >> y;
    if (ss.fail())
        return nullptr;
    target = {x, y};
    return new Commands::QuadraticConnected(coordinateType, target);
}

Ref<Document> Parser::parse(const std::string &source)
{
    tinyxml2::XMLDocument xmlDocument;
    xmlDocument.Parse(source.c_str(), source.size());
    if (xmlDocument.ErrorID() != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Error parsing XML: " << xmlDocument.ErrorName() << std::endl;
        return nullptr;
    }
    tinyxml2::XMLElement *rootNode = xmlDocument.RootElement();
    if (rootNode == nullptr || std::strcmp(rootNode->Value(), "svg") != 0)
    {
        std::cout << "Root node is not svg" << std::endl;
        return nullptr;
    }
    glm::vec2 dimensions = Parser::getDocumentDimensions(xmlDocument);
    std::string documentName = Parser::getDocumentName(xmlDocument);
    std::unordered_map<std::string, std::string> rawPaths = Parser::getRawPaths(xmlDocument);
    std::vector<Ref<Path>> paths;
    for (const auto &rawPath : rawPaths)
    {
        std::vector<Commands::Command *> parsedCommands = Parser::parseStringCommands(rawPath.second);
        const std::string &pathName = rawPath.second;
        paths.push_back(MakeRef<Path>(pathName, parsedCommands));
    }

    return MakeRef<Document>(documentName, dimensions, paths);
}

//std::vector<Ref<Path>> Parser::parse(const std::string &source)
//{
//    std::unordered_map<std::string, std::string> rawPaths = Parser::readSvgPaths(source);
//    std::vector<Ref<Path>> paths;
//    for (const auto &rawPath : rawPaths)
//    {
//        std::vector<Commands::Command *> commands = Parser::parseCommands(rawPath.second);
//        paths.push_back(MakeRef<Path>(rawPath.first, commands));
//    }
//    return paths;
//}

}

}
