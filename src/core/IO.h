#ifndef VANADIUM_IO_H
#define VANADIUM_IO_H

#include <vector>
#include <tuple>

#include <glm/vec2.hpp>

namespace Vanadium
{

class IO
{
private:
    static IO *instance;

    static IO *create();

public:
    virtual std::vector<int8_t> readFile(const std::string &path) = 0;
    virtual void writeData(const std::string &path, void *data, size_t dataSize, bool overwrite) = 0;
    virtual void writeData(const std::string &path, const std::vector<int8_t> &data, bool overwrite) = 0;
    virtual std::pair<glm::ivec2, std::vector<int8_t>> readPng(const std::string &path) = 0;
    virtual std::pair<glm::ivec2, std::vector<int8_t>> readBmp(const std::string &path) = 0;
    // Why?
    virtual std::pair<glm::ivec2, std::vector<int8_t>> readJpeg(const std::string &path) = 0;

    static IO *getInstance();
};

}

#endif //VANADIUM_IO_H
