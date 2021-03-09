#include "Figure.h"
using namespace Vanadium;

bool FigureFactory::isJsonValidFigure(const nlohmann::json &figure, const std::string &path) {
    VNuint verifiedFrames = 0;

    if (!figure.is_structured() &&
        !figure.contains("name") || !figure.contains("frames") &&
                                    !figure["frames"].is_array())
    {
        VAN_USER_ERROR("{} has invalid structure.", path);
        return false;
    }
    if (figure["frames"].size() <= 1)
    {
        VAN_USER_ERROR("{} \"frames\" has not enough frames.", path);
        return false;
    }
    for (const auto &test : figure["frames"])
    {
        if (test.is_structured() && test.size() == 2 &&
            test.contains("name") && test.contains("path") &&
            test["name"].is_string() && test["path"].is_string())
        {
            verifiedFrames++;
        }
    }
    if (verifiedFrames < 2)
    {
        VAN_USER_ERROR("{} \"frames\" has not enough frames.", path);
        return false;
    }
    return true;
}

Ref<Figure> FigureFactory::parseSvgs(const std::unordered_map<std::string, std::string> &figurePaths, const std::string &figureName)
{
    Ref<Figure> fig = MakeRef<Figure>();
    Vfs::ErrorCode err;

    fig->name = figureName;
    for (const auto &figurePair : figurePaths)
    {
        const std::string &name = figurePair.first;
        const std::string &path = figurePair.second;
        const std::string svgSource = Vfs::readAsString(path);
        Ref<Svg::Document> document;

        err = Vfs::getErrorCode();
        if (err != Vfs::ErrorCode::OK)
        {
            VAN_USER_ERROR("Cannot read file \"{}\" from VFS: {}", path, Vfs::errorCodeToString(err));
            continue;
        }
        document = Svg::Parser::parse(svgSource);
        if (!document)
        {
            VAN_USER_ERROR("Error SVG parsing \"{}\"", path);
            continue;
        }
        fig->frames[name] = document;
    }
    if (fig->frames.size() < 2)
    {
        return nullptr;
    }
    return fig;
}

Ref<Figure> FigureFactory::figureFactory(const std::string &path)
{
    nlohmann::json figure;
    const std::string figureString = Vfs::readAsString(path);
    std::unordered_map<std::string, std::string> frames;
    Vfs::ErrorCode err;

    err = Vfs::getErrorCode();
    if (err != Vfs::ErrorCode::OK)
    {
        VAN_USER_ERROR("Cannot read file \"{}\" from VFS: {}", path, Vfs::errorCodeToString(err));
        return nullptr;
    }
    try
    {
        figure = nlohmann::json::parse(path);
    }
    catch(const nlohmann::detail::parse_error &e)
    {
        VAN_USER_ERROR("Error parsing {}", path);
        return nullptr;
    }
    if (!FigureFactory::isJsonValidFigure(figure, path))
    {
        return nullptr;
    }
    for (const auto &test : figure["frames"])
    {
        if (test.is_structured() && test.size() == 2 &&
            test.contains("name") && test.contains("path") &&
            test["name"].is_string() && test["path"].is_string())
        {
            frames[test["name"]] = test["path"];
        }
    }
    return FigureFactory::parseSvgs(frames, figure["name"]);
}
