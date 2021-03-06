#include "DefaultIO.h"

#include <fstream>
#include <filesystem>

#include "../../core/Log.h"

namespace Vanadium
{

#if __cplusplus >= 201703L
bool DefaultIO::fail() noexcept
{
    return this->isFail;
}

std::vector<char> DefaultIO::read(const std::string &path) noexcept
{
    std::ifstream file(path, std::ios::binary);
    std::vector<char> data;

    if (!file)
    {
        this->isFail = true;
        return data;
    }

    file.seekg(0, std::ios_base::end);
    VNsize size = (VNsize)file.tellg();
    data.resize(size);
    file.seekg(0, std::ios_base::beg);
    file.read(&data[0], (long)size);
    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
    return data;
}

std::string DefaultIO::readAsString(const std::string &path) noexcept
{
    std::stringstream ss;
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        this->isFail = true;
        return std::string();
    }
    ss << file.rdbuf();
    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
    return ss.str();
}

void DefaultIO::write(const std::string &path, void *data, VNsize dataSize, bool overwrite) noexcept
{
    std::ofstream file;

    if (overwrite)
        file = std::ofstream(path, std::ios::binary | std::ios::trunc);
    else
        file = std::ofstream(path, std::ios::binary | std::ios_base::app);
    if (!file)
    {
        this->isFail = true;
        return;
    }
    file.write((char *)data, (long)dataSize);
    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
}

std::vector<std::string> DefaultIO::listDirectory(const std::string &path) noexcept
{
    std::vector<std::string> dirList;
    std::error_code err;

    for (const auto &entry : std::filesystem::directory_iterator(path, err))
        dirList.emplace_back(entry.path());
    this->isFail = (bool)err;
    return dirList;
}

void DefaultIO::removeAll(const std::string &path) noexcept
{
    std::error_code err;

    std::filesystem::remove_all(path, err);
    this->isFail = (bool)err;
}

void DefaultIO::remove(const std::string &path) noexcept
{
    std::error_code err;

    std::filesystem::remove(path, err);
    this->isFail = (bool)err;
}

void DefaultIO::createFile(const std::string &path) noexcept
{
    std::ofstream file(path);

    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
}

void DefaultIO::makeDir(const std::string &path) noexcept
{
    std::error_code err;

    std::filesystem::create_directory(path, err);
    this->isFail = (bool)err;
}

void DefaultIO::makeDirs(const std::string &path) noexcept
{
    std::error_code err;

    std::filesystem::create_directories(path, err);
    this->isFail = (bool)err;
}

VNsize DefaultIO::fileSize(const std::string &path) noexcept
{
    std::error_code err;
    VNsize size = std::filesystem::file_size(path, err);

    this->isFail = (bool)err;
    return size;
}

bool DefaultIO::fileExists(const std::string &path) noexcept
{
    std::error_code err;
    bool result = std::filesystem::exists(path, err);

    this->isFail = (bool)err;
    return result;
}

bool DefaultIO::isRegularFile(const std::string &path) noexcept
{
    std::error_code err;
    bool result = std::filesystem::is_regular_file(path, err);

    this->isFail = (bool)err;
    return result;
}

bool DefaultIO::isDirectory(const std::string &path) noexcept
{
    std::error_code err;
    bool result = std::filesystem::is_directory(path, err);

    this->isFail = (bool)err;
    return result;
}
#else
#warning "DefaultIO in current C++(< C++17) standard has no implementations for many methods! Not implemented methods will throw exceptions."
bool DefaultIO::fail()
{
    return this->isFail;
}

std::vector<char> DefaultIO::readFile(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    std::vector<char> data;

    if (!file)
    {
        this->isFail = true;
        return data;
    }

    file.seekg(0, std::ios_base::end);
    VNsize size = file.tellg();
    data.resize(size);
    file.seekg(0, std::ios_base::beg);
    file.read(&data[0], size);
    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
    return data;
}

void DefaultIO::writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite)
{
    std::ofstream file;

    if (overwrite)
        file = std::ofstream(path, std::ios::binary | std::ios::trunc);
    else
        file = std::ofstream(path, std::ios::binary | std::ios_base::app);
    if (!file)
    {
        this->isFail = true;
        return;
    }
    file.write((char *)data, dataSize);
    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
}

std::vector<std::string> DefaultIO::listDirectory(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

void DefaultIO::removeAll(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

void DefaultIO::remove(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

void DefaultIO::createFile(const std::string &path)
{
    std::ofstream file(path);

    if (!file)
        this->isFail = true;
    else
        this->isFail = false;
}

void DefaultIO::makeDir(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

void DefaultIO::makeDirs(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

VNsize DefaultIO::fileSize(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

bool DefaultIO::fileExists(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

bool DefaultIO::isRegularFile(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}

bool DefaultIO::isDirectory(const std::string &path)
{
    throw std::runtime_error("std::filesystem is not supported in current C++ standard.");
}
#endif

}