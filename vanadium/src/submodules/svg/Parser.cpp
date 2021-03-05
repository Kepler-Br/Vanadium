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

//    if (width == nullptr)
//        dimensions.x = 0;
//    else
//    {
//        float val;
//        ss = std::stringstream (width);
//        ss >> val;
//        if (ss.fail())
//            dimensions.x = 0;
//        else
//            dimensions.x = val;
//    }
//    if (height == nullptr)
//        dimensions.y = 0;
//    else
//    {
//        float val;
//        ss = std::stringstream (height);
//        ss >> val;
//        if (ss.fail())
//            dimensions.y = 0;
//        else
//            dimensions.y = val;
//    }
//    if (dimensions.x == 0.0f && dimensions.y == 0.0f)
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

class XmlVisitor : public tinyxml2::XMLVisitor
{
private:
    struct XmlRawLayer
    {
        const tinyxml2::XMLElement *layerPtr = nullptr;
        std::vector<const tinyxml2::XMLElement *> paths;
    };

private:
    std::unordered_map<uintptr_t, XmlRawLayer> layers;

    bool elementHasStyleDisplayNone(const tinyxml2::XMLElement *element)
    {
        if (element == nullptr)
            return false;
        const char *styleCString = element->Attribute("style");
        if (styleCString == nullptr)
            return false;
        std::string styleString = styleCString;
        auto pos = styleString.find("display:none");
        if (pos != std::string::npos)
            return true;
        return false;
    }

public:
    bool VisitEnter( const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *attribute ) override
    {
        if (std::strcmp(element.Value(), "path") == 0)
        {

            if (this->elementHasStyleDisplayNone(&element))
                return true;
            const tinyxml2::XMLElement *parent = element.Parent()->ToElement();
            uintptr_t parentId;
            if (parent == nullptr || strcmp(parent->Value(), "g") != 0)
                parentId = 0;
            else
                parentId = (uintptr_t)parent;
            if (this->elementHasStyleDisplayNone(parent))
                return true;
            auto foundXmlRawLayer = this->layers.find(parentId);
            if (foundXmlRawLayer == this->layers.end())
            {
                XmlRawLayer newLayer;
                newLayer.layerPtr = parent;
                newLayer.paths.push_back(&element);
                this->layers[parentId] = newLayer;
            }
            else
            {
                foundXmlRawLayer->second.paths.push_back(&element);
            }
        }
        return true;
    }

    std::unordered_map<std::string, std::vector<std::string>> getLayers()
    {
        std::unordered_map<std::string, std::vector<std::string>> converted;

        for (const auto &layer : this->layers)
        {
            std::string layerName;
            if (layer.first == 0)
                layerName = "Undetermined";
            else
            {
                const char *nameCString = layer.second.layerPtr->Attribute("id");
                layerName = nameCString == nullptr ? Tools::randomString(10) : nameCString;
            }
            converted[layerName] = std::vector<std::string>();
            for (auto &path : layer.second.paths)
            {
                const char *commandsCString = path->Attribute("d");
                if (commandsCString == nullptr)
                    continue;
                const std::string commands = commandsCString;
                converted[layerName].push_back(commands);
            }
        }
        return converted;
    }
};

std::unordered_map<std::string, std::vector<std::string>> Parser::getRawLayers(tinyxml2::XMLDocument &xmlDocument)
{
    std::unordered_map<std::string, std::vector<std::string>> rawLayers;
    tinyxml2::XMLElement *rootNode = xmlDocument.RootElement();
    XmlVisitor xmlVisitor;

    rootNode->Accept(&xmlVisitor);
    return xmlVisitor.getLayers();
}

const char *Parser::skipDouble(const char *str)
{
    bool dotPassed = false;
    bool ePassed = false;
    bool minusPassed = false;

    if (str == nullptr)
        return str;
    if (*str == '-')
    {
        minusPassed = true;
        str++;
    }
    while (*str != '\0')
    {
        if (*str == '-' && minusPassed)
            break;
        if (*str == '-')
            minusPassed = true;
        if ((*str == 'e' || *str == 'E') && ePassed)
            break;
        if (*str == '.' && dotPassed)
            break;
        if (*str == '.')
            dotPassed = true;
        if (*str == 'e' || *str == 'E')
        {
            minusPassed = false;
            ePassed = true;
        }
        if (*str == '-' || *str == '.' || *str == 'e' || *str == 'E' || std::isdigit(*str))
            str++;
        else
            break;
    }
    return str;
}

bool Parser::isDouble(char ch)
{
    if (ch == '-' || ch == '.' || std::isdigit(ch))
        return true;
    return false;
}

const char *Parser::skipWhitespace(const char *str)
{
    if (str == nullptr)
        return str;
    while (*str != '\0')
    {
        if (std::isspace(*str))
            str++;
        else
            break;
    }
    return str;
}

std::vector<Commands::Command *> Parser::parseStringCommands(const std::string &commandsString)
{
    const char *cString = commandsString.c_str();
    std::vector<Commands::Command *> commands;

    while (*cString != '\0')
    {
        if (!Parser::isCommand(*cString))
        {
            cString++;
            continue;
        }
        Commands::Type commandType = charToCommandType(*cString);
        Commands::Command *command = nullptr;
        switch (commandType)
        {
            case Commands::Type::Cubic:
                command = Parser::parseCubic(&cString);
                break;
            case Commands::Type::Move:
                command = Parser::parseMove(&cString);
                break;
            case Commands::Type::Line:
                command = Parser::parseLine(&cString);
                break;
            case Commands::Type::HorizontalLine:
//                command = Parser::parseHLine(&cString);
                break;
            case Commands::Type::VerticalLine:
//                command = Parser::parseVLine(&cString);
                break;
            case Commands::Type::ClosePath:
                command = Parser::parseClosePath(&cString);
                break;
            case Commands::Type::Quadratic:
//                command = Parser::parseQuadratic(commandChar, ss);
                break;
            case Commands::Type::CubicConnected:
//                command = Parser::parseCubicConnected(&cString);
                break;
            case Commands::Type::QuadraticConnected:
//                command = Parser::parseQuadraticConnected(commandChar, ss);
                break;
            case Commands::Type::Unknown:
            default:
                std::cout << "\"" << *cString << "\"" <<  " command is not parsable yet!" << std::endl;
                cString++;
                continue;
        }
        if (command == nullptr)
        {
            std::cout << "Command \"" << *cString << "\" is not parsable yet." << std::endl;
//            std::cout << cString << std::endl;
            cString++;
            continue;
        }
        commands.push_back(command);
    }
    return commands;
}

bool Parser::parseVec2(const char **str, glm::vec2 &val)
{
    if (**str == '\0' || !isDouble(**str))
        return false;
    val.x = (float)std::atof(*str);
    *str = skipDouble(*str);
    *str = skipWhitespace(*str);
    if (**str == ',')
        (*str)++;
    *str = skipWhitespace(*str);
    if (**str == '\0' || !isDouble(**str))
        return false;
    val.y = (float)std::atof(*str);
    *str = skipDouble(*str);
    *str = skipWhitespace(*str);
    if (**str == ',')
        (*str)++;
    return true;
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

Commands::Cubic *Parser::parseCubic(const char **cString)
{
    std::vector<glm::vec2> points;
    Commands::CoordinateType coordinateType;

    coordinateType = Parser::charToCoordinateType(**cString);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    (*cString)++;
    while (true)
    {
        glm::vec2 point;
        *cString = skipWhitespace(*cString);
        if (**cString == '\0' || !isDouble(**cString))
            break;
        if (!Parser::parseVec2(cString, point))
            break;
        points.push_back(point);
    }
    return new Commands::Cubic(coordinateType, points);
}

Commands::Move *Parser::parseMove(const char **cString)
{
    std::vector<glm::vec2> points;
    Commands::CoordinateType coordinateType;

    coordinateType = Parser::charToCoordinateType(**cString);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    (*cString)++;
    *cString = skipWhitespace(*cString);
    while (true)
    {
        glm::vec2 point;
        *cString = skipWhitespace(*cString);
        if (**cString == '\0' || !isDouble(**cString))
            break;
        if (!Parser::parseVec2(cString, point))
            break;
        points.push_back(point);
    }
    return new Commands::Move(coordinateType, points);
}

Commands::Line *Parser::parseLine(const char **cString)
{
//    glm::vec2 point;
    std::vector<glm::vec2> points;
    Commands::CoordinateType coordinateType;

    coordinateType = Parser::charToCoordinateType(**cString);
    if (coordinateType == Commands::CoordinateType::Unknown)
        return nullptr;
    (*cString)++;
    while (true)
    {
        glm::vec2 point;
        *cString = skipWhitespace(*cString);
        if (**cString == '\0' || !isDouble(**cString))
            break;
        if (!Parser::parseVec2(cString, point))
            break;
        points.push_back(point);
    }
    return new Commands::Line(coordinateType, points);
}

//Commands::HLine *Parser::parseHLine(const char **cString)
//{
//    float target;
//    Commands::CoordinateType coordinateType;
//
//    coordinateType = Parser::charToCoordinateType(**cString);
//    if (coordinateType == Commands::CoordinateType::Unknown)
//        return nullptr;
//    (*cString)++;
//    *cString = skipWhitespace(*cString);
//    if (**cString == '\0' || !isDouble(**cString))
//        return nullptr;
//    target = (float)std::atof(*cString);
//    *cString = skipDouble(*cString);
//    return new Commands::HLine(coordinateType, target);
//}
//
//Commands::VLine *Parser::parseVLine(const char **cString)
//{
//    float target;
//    Commands::CoordinateType coordinateType;
//
//    coordinateType = Parser::charToCoordinateType(**cString);
//    if (coordinateType == Commands::CoordinateType::Unknown)
//        return nullptr;
//    (*cString)++;
//    *cString = skipWhitespace(*cString);
//    if (**cString == '\0' || !isDouble(**cString))
//        return nullptr;
//    target = (float)std::atof(*cString);
//    *cString = skipDouble(*cString);
//    return new Commands::VLine(coordinateType, target);
//}

Commands::ClosePath *Parser::parseClosePath(const char **cString)
{
    (*cString)++;

    return new Commands::ClosePath();
}

//Commands::Quadratic *Parser::parseQuadratic(char commandChar, std::stringstream &ss)
//{
////    QuadraticPoints points;
////    Commands::CoordinateType coordinateType;
////    float x, y;
////    char comma;
////
////    coordinateType = Parser::charToCoordinateType(commandChar);
////    if (coordinateType == Commands::CoordinateType::Unknown)
////        return nullptr;
////    ss >> x >> comma >> y;
////    if (ss.fail() || comma != ',')
////        return nullptr;
////    std::get<0>(points) = {x, y};
////    ss >> x >> comma >> y;
////    if (ss.fail() || comma != ',')
////        return nullptr;
////    std::get<1>(points) = {x, y};
////    return new Commands::Quadratic(coordinateType, points);
//}
//Commands::CubicConnected *Parser::parseCubicConnected(const char **cString)
//{
//    std::pair<glm::vec2, glm::vec2> points;
//    Commands::CoordinateType coordinateType;
//
//    coordinateType = Parser::charToCoordinateType(**cString);
//    if (coordinateType == Commands::CoordinateType::Unknown)
//        return nullptr;
//    (*cString)++;
//    *cString = skipWhitespace(*cString);
//    if (**cString == '\0' || !isDouble(**cString))
//        return nullptr;
//    if (!Parser::parseVec2(cString, std::get<0>(points)))
//        return nullptr;
//    if (!Parser::parseVec2(cString, std::get<1>(points)))
//        return nullptr;
//    return new Commands::CubicConnected(coordinateType, points);
//}

//Commands::QuadraticConnected *Parser::parseQuadraticConnected(char commandChar, std::stringstream &ss)
//{
////    glm::vec2 target;
////    Commands::CoordinateType coordinateType;
////    float x, y;
////
////    coordinateType = Parser::charToCoordinateType(commandChar);
////    if (coordinateType == Commands::CoordinateType::Unknown)
////        return nullptr;
////    ss >> x >> y;
////    if (ss.fail())
////        return nullptr;
////    target = {x, y};
////    return new Commands::QuadraticConnected(coordinateType, target);
//}

Document *Parser::parse(const std::string &source)
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
    std::unordered_map<std::string, std::vector<std::string>> rawLayers = Parser::getRawLayers(xmlDocument);
    std::vector<Layer *> layers;
    for (const auto &rawLayer : rawLayers)
    {
        std::string layerName = rawLayer.first;
        std::vector<Path *> paths;
        for (const auto &rawPath : rawLayer.second)
        {
            std::vector<Commands::Command *> parsedCommands = Parser::parseStringCommands(rawPath);
            Path *path = new Path(parsedCommands);
            paths.push_back(path);
        }
        Layer *layer = new Layer(layerName, paths);
        layers.push_back(layer);
    }
    return new Document(documentName, dimensions, layers);
}

}

}
