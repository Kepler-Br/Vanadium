#ifndef VANADIUM_DOCUMENT_H
#define VANADIUM_DOCUMENT_H

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

#include "Path.h"

namespace Vanadium
{

namespace Svg
{

class Document
{
private:
    std::vector<Ref<Path>> pathList;
    std::unordered_map<std::string, Ref<Path>> pathMap;
    glm::vec2 dimensions;
    std::string name;

    void mapPathList() noexcept
    {
        for (const auto &path : this->pathList)
        {
            pathMap[path->getName()] = path;
        }
    }

public:
    Document(std::string name, glm::vec2 dimensions, std::vector<Ref<Path>> pathList) :
        pathList(std::move(pathList)),
        dimensions(dimensions),
        name(std::move(name))
    {
        this->mapPathList();
    }

    [[nodiscard]]
    const glm::vec2 &getDimensions() const noexcept
    {
        return this->dimensions;
    }

    [[nodiscard]]
    Ref<Path> getPathByName(const std::string &pathName)
    {
        auto path = this->pathMap.find(pathName);

        if (path == this->pathMap.end())
            return nullptr;
        return path->second;
    }

    [[nodiscard]]
    const std::vector<Ref<Path>> &getPaths() const noexcept
    {
        return this->pathList;
    }

    [[nodiscard]]
    std::string getName() const noexcept
    {
        return this->name;
    }

    [[nodiscard]]
    VNsize getTotalPaths() const noexcept
    {
        return this->pathList.size();
    }

};

}

}

#endif //VANADIUM_DOCUMENT_H
