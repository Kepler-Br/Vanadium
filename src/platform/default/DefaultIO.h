#ifndef VANADIUM_DEFAULTIO_H
#define VANADIUM_DEFAULTIO_H

#include "../../core/IO.h"

#include <fstream>

namespace Vanadium
{

class DefaultIO : public IO
{
private:
    static size_t getFileSize(std::ifstream &file);
    static std::pair<glm::ivec2, std::vector<int8_t>> readImage(const std::string &path);
public:
    std::vector<int8_t>  readFile(const std::string &path) override;
    void writeData(const std::string &path, void *data, size_t dataSize, bool overwrite) override;
    void writeData(const std::string &path, const std::vector<int8_t> &data, bool overwrite) override;
    std::pair<glm::ivec2, std::vector<int8_t>> readPng(const std::string &path) override;
    std::pair<glm::ivec2, std::vector<int8_t>> readBmp(const std::string &path) override;
    std::pair<glm::ivec2, std::vector<int8_t>> readJpeg(const std::string &path) override;
};

}

#endif //VANADIUM_DEFAULTIO_H
