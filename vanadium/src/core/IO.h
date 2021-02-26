#ifndef VANADIUM_IO_H
#define VANADIUM_IO_H

#include <vector>
#include <tuple>

#include <glm/vec2.hpp>

#include "Types.h"

namespace Vanadium
{

class IO
{
private:
    static IO *instance;

    static IO *create();

public:
    virtual std::vector<int8_t> readFile(const std::string &path) = 0;
    virtual void writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite) = 0;
    virtual void writeFile(const std::string &path, const std::vector<int8_t> &data, bool overwrite) = 0;
    // virtual std::vector<std::string> getDirectoryContents(const std::string &path) = 0;

    static IO *getInstance();
};

}

#endif //VANADIUM_IO_H
