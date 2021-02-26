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

public:
    std::vector<int8_t> readFile(const std::string &path) override;
    void writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite) override;
    void writeFile(const std::string &path, const std::vector<int8_t> &data, bool overwrite) override;
    std::vector<std::string> getDirectoryContents(const std::string &path) override;
};

}

#endif //VANADIUM_DEFAULTIO_H
