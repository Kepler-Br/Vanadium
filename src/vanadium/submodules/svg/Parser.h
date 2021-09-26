#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Commands.h"
#include "Document.h"
#include "Path.h"
#include "Types.h"
#include "vanadium/core/types/Reference.h"

namespace tinyxml2 {
class XMLDocument;
}

namespace vanadium::svg {

class Parser {
 private:
  static const std::unordered_map<char, commands::CoordinateType>
      commandCharToCoordinateTypeMap;
  static const std::unordered_map<char, commands::Type> commandCharToTypeMap;
  static const std::unordered_set<char> commandChars;

  static glm::vec2 getDocumentDimensions(tinyxml2::XMLDocument &xmlDocument);
  static std::string getDocumentName(tinyxml2::XMLDocument &xmlDocument);
  static std::unordered_map<std::string, std::vector<std::string>> getRawLayers(
      tinyxml2::XMLDocument &xmlDocument);
  static std::vector<commands::Command *> parseStringCommands(
      const std::string &commandsString);

  //    static std::unordered_map<std::string, std::string> readSvgPaths(const
  //    std::string &source); static std::vector<Commands::Command *>
  //    parseCommands(const std::string &rawCommands);

  static const char *skipDouble(const char *str);
  static bool isDouble(char ch);
  static const char *skipWhitespace(const char *str);
  static bool parseVec2(const char **str, glm::vec2 &val);
  static commands::CoordinateType charToCoordinateType(char command);
  static commands::Type charToCommandType(char command);
  static bool isCommand(char command);
  static commands::Move *parseMove(const char **cString);
  static commands::Line *parseLine(const char **cString);
  static commands::HLine *parseHLine(const char **cString);
  static commands::VLine *parseVLine(const char **cString);
  static commands::ClosePath *parseClosePath(const char **cString);
  static commands::Cubic *parseCubic(const char **cString);
  //    static Commands::Quadratic *parseQuadratic(char commandChar,
  //    std::stringstream &ss);
  static commands::CubicConnected *parseCubicConnected(const char **cString);
  //    static Commands::QuadraticConnected *parseQuadraticConnected(char
  //    commandChar, std::stringstream &ss);

 public:
  Parser() = delete;

  //    static std::vector<Ref<Path>> parse(const std::string &source);
  static Ref<Document> parse(const std::string &source);
};

}  // namespace vanadium::svg
