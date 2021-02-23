#include "DefaultIO.h"
#include <fstream>

#include "../../core/Log.h"
#include <SDL2/SDL_image.h>


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


std::pair<glm::ivec2, std::vector<int8_t>> DefaultIO::readImage(const std::string &path)
{
    std::vector<int8_t> data;
    glm::ivec2 resolution;
    SDL_Surface *surface;
    size_t pixelCount;
    size_t bytesTotal;

    VAN_ENGINE_TRACE("Loading image: \"{}\"", path);
    surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        VAN_ENGINE_ERROR("Cannot load texture: {}", path);
        return std::make_pair(glm::ivec2(0), std::vector<int8_t>());
    }
    resolution = glm::ivec2(surface->w, surface->h);
    pixelCount = surface->w * surface->h;
    bytesTotal = pixelCount * surface->format->BytesPerPixel * sizeof(int8_t);
    data.resize(bytesTotal);
    std::memcpy(data.data(), surface->pixels, bytesTotal);
    SDL_FreeSurface(surface);
    return std::make_pair(resolution, data);
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

void DefaultIO::writeData(const std::string &path, void *data, size_t dataSize, bool overwrite)
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

void DefaultIO::writeData(const std::string &path, const std::vector<int8_t> &data, bool overwrite)
{
    this->writeData(path, (void *)&data[0], data.size(), overwrite);
}

std::pair<glm::ivec2, std::vector<int8_t>> DefaultIO::readPng(const std::string &path)
{
    return DefaultIO::readImage(path);
}

std::pair<glm::ivec2, std::vector<int8_t>> DefaultIO::readBmp(const std::string &path)
{
    return DefaultIO::readImage(path);
}

std::pair<glm::ivec2, std::vector<int8_t>> DefaultIO::readJpeg(const std::string &path)
{
    return DefaultIO::readImage(path);
}

}