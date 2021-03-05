#ifndef VANADIUM_LAYER_H
#define VANADIUM_LAYER_H

#include "Path.h"

namespace Vanadium
{

namespace Svg
{

class Layer
{
private:
    std::vector<Path *> paths;
    std::string name;

public:
    Layer(std::string name, std::vector<Path *> paths) :
        name(std::move(name)),
        paths(std::move(paths))
    {}

    ~Layer()
    {
        for (auto *path : paths)
        {
            delete path;
        }
    }

    const std::string &getName() const
    {
        return this->name;
    }

    [[nodiscard]]
    Path *getPathById(VNsize id) const
    {
        if (id >= this->paths.size())
            return nullptr;
        return this->paths[id];
    }

    VNsize getTotalPaths() const
    {
        return this->paths.size();
    }

    const std::vector<Path *> &getPaths() const
    {
        return this->paths;
    }
};

}

}

#endif //VANADIUM_LAYER_H
