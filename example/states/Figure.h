#ifndef VANADIUM_FIGURE_H
#define VANADIUM_FIGURE_H

#include "include/vanadium/Vanadium.h"
#include <unordered_map>
#include <nlohmann/json.hpp>

struct Figure
{
    std::string name;
    std::unordered_map<std::string, Vanadium::Ref<Vanadium::Svg::Document>> frames;
};

class FigureFactory
{
private:
    static bool isJsonValidFigure(const nlohmann::json &figure, const std::string &path);
    static Vanadium::Ref<Figure> parseSvgs(const std::unordered_map<std::string, std::string> &figurePaths, const std::string &figureName);

public:
    static Vanadium::Ref<Figure> figureFactory(const std::string &path);
};

#endif //VANADIUM_FIGURE_H
