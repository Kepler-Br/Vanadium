#include "Parser.h"

#include <utility>
#include <tinyxml2.h>
#include <sstream>
#include <iostream>
#include <cstring>

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
        {'C', Commands::Type::Cubic},
        {'Q', Commands::Type::Quadratic},
        {'s', Commands::Type::CubicConnected},
        {'S', Commands::Type::CubicConnected},
};

const std::unordered_set<char> Parser::commandChars = {
        'm',
        'M',
        'l',
        'L',
        'h',
        'H',
        'h',
        'H',
        'z',
        'Z',
        'C',
        'Q',
        's',
        'S',
};

void Parser::readSvgPaths(const std::string &source)
{
    tinyxml2::XMLDocument doc;
    doc.Parse(source.c_str(), source.size());
    if (doc.ErrorID() != tinyxml2::XML_SUCCESS)
    {
        std::stringstream msg;
        throw std::runtime_error(
                dynamic_cast<std::stringstream&>
                (msg
                        << "Error parsing SVG file. XML error: "
                        << doc.ErrorStr() << "."
                ).str());
    }

    tinyxml2::XMLElement *rootNode = doc.RootElement();
    if (std::strcmp(rootNode->Value(), "svg") != 0)
    {
        std::stringstream msg;
        throw std::runtime_error(
                dynamic_cast<std::stringstream&>
                (msg
                        << "Not a svg file."
                ).str());
    }
    tinyxml2::XMLElement *pathsNode = rootNode->FirstChildElement("g");
    if (pathsNode == nullptr)
    {
        std::stringstream msg;
        throw std::runtime_error(
                dynamic_cast<std::stringstream&>
                (msg
                        << "SVG file has no g node."
                ).str());
    }
    for (tinyxml2::XMLElement* child = pathsNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        const std::string &pathId = child->Attribute("id");
        const std::string &commands = child->Attribute("d");
        this->svgRawPaths[pathId] = commands;
    }
    if (this->svgRawPaths.empty())
    {
        std::stringstream msg;
        throw std::runtime_error(
                dynamic_cast<std::stringstream&>
                (msg
                        << "SVG file has no paths."
                ).str());
    }
}

void Parser::parseCommands(const std::string &rawCommands)
{
    std::cout << rawCommands << std::endl;
    std::stringstream ss(rawCommands);
    while(!ss.eof())
    {
        char ch;
        ss >> ch;
        if (!Parser::isCommand(ch))
            continue;
        Commands::Type commandType = charToCommandType(ch);
        if (commandType == Commands::Type::Move)
        {
            char comma;
            float x, y;
            ss >> x >> comma >> y;
            if (ss.fail())
            {
                std::cout << "Incorrect move command!" << std::endl;
                ss.clear();
                continue;
            }
            std::cout << "Move to: " << x << ", " << y << std::endl;
        }
        if (commandType == Commands::Type::Cubic)
        {
            Commands::Cubic *command = Parser::parseCubic(ss);
            std::cout << "Parsed cubic command: " << command->joints[0].x;
            delete command;
        }
//        std::cout << ch << std::endl;
    }
//    const char *stringPointer = rawCommands.c_str();
//    while (*stringPointer != '\0')
//    {
//        stringPointer = Parser::skipNotCommands(stringPointer);
//        Parser::CommandType commandType = Parser::charToCommandType(*stringPointer);
//        Parser::CommandCoordinateType coordinateType = Parser::charToCoordinateType(*stringPointer);
//    }



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

Commands::Cubic *Parser::parseCubic(std::stringstream &ss)
{

}

//const char *Parser::skipWhiteSpace(const char *str)
//{
//    while (std::isspace((int)*str))
//    {
//        str++;
//    }
//    return str;
//}
//
//const char *Parser::skipNotCommands(const char *str)
//{
//    while (*str != '\0' || Parser::isCommand(*str))
//    {
//        str++;
//    }
//    return str;
//}

Parser::Parser(const std::string &source)
{
    this->readSvgPaths(source);
    this->parseCommands(this->svgRawPaths.begin()->second);
}

}

}
