#include "DefaultIO.h"

#include <fstream>

#include "../../core/Log.h"

namespace Vanadium
{

size_t DefaultIO::getFileSize(std::ifstream &file)
{
    size_t fileSize;

    fileSize = file.tellg();
    file.seekg(0, std::ios::end);
    fileSize = (size_t)file.tellg() - fileSize;
    file.seekg(0, std::ios::beg);
    return fileSize;
}

std::vector<int8_t> DefaultIO::readFile(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    std::vector<int8_t> data;
    size_t fileSize;

    if (!file)
    {
        VAN_ENGINE_ERROR("Error reading file \"{}\"", path);
        return data;
    }
    VAN_ENGINE_TRACE("Reading file: \"{}\"", path);
    fileSize = DefaultIO::getFileSize(file);
    data.resize(fileSize);
    file.read((char *)&data[0], fileSize);
    file.close();
    return data;
}

void DefaultIO::writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite)
{
    std::ofstream file;

    VAN_ENGINE_TRACE("Writing file: \"{}\"", path);
    if (overwrite)
        file = std::ofstream(path, std::ios::binary | std::ios::trunc);
    else
        file = std::ofstream(path, std::ios::binary | std::ios_base::app);
    if (!file)
    {
        VAN_ENGINE_ERROR("Error writing file \"{}\"", path);
        return;
    }
    file.write((char *)data, dataSize);
    file.close();
}

void DefaultIO::writeFile(const std::string &path, const std::vector<int8_t> &data, bool overwrite)
{
    this->writeFile(path, (void *) &data[0], data.size(), overwrite);
}

// std::vector<std::string> DefaultIO::getDirectoryContents(const std::string &path)
// {
//     #warning "getDirectoryContents is not implemented."
//     return std::vector<std::string>({"NO"});
// }

}