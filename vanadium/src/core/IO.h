#ifndef VANADIUM_IO_H
#define VANADIUM_IO_H

#include <vector>
#include <sstream>
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
#if __cplusplus >= 201703L
    virtual bool fail() noexcept = 0;
    virtual std::string readAsString(const std::string &path) noexcept = 0;
    virtual std::vector<char> read(const std::string &path) noexcept = 0;
    virtual void write(const std::string &path, void *data, VNsize dataSize, bool overwrite) noexcept = 0;
    virtual std::vector<std::string> listDirectory(const std::string &path) noexcept = 0;
    virtual void removeAll(const std::string &path) noexcept = 0;
    virtual void remove(const std::string &path) noexcept = 0;
    virtual void createFile(const std::string &path) noexcept = 0;
    virtual void makeDir(const std::string &path) noexcept = 0;
    virtual void makeDirs(const std::string &path) noexcept = 0;
    virtual VNsize fileSize(const std::string &path) noexcept = 0;
    virtual bool fileExists(const std::string &path) noexcept = 0;
    virtual bool isRegularFile(const std::string &path) noexcept = 0;
    virtual bool isDirectory(const std::string &path) noexcept = 0;
#else
    virtual bool fail() = 0;
    virtual std::vector<char> readFile(const std::string &path) = 0;
    virtual void writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite) = 0;
    virtual std::vector<std::string> listDirectory(const std::string &path) = 0;
    virtual void removeAll(const std::string &path) = 0;
    virtual void remove(const std::string &path) = 0;
    virtual void createFile(const std::string &path) = 0;
    virtual void makeDir(const std::string &path) = 0;
    virtual void makeDirs(const std::string &path) = 0;
    virtual VNsize fileSize(const std::string &path) = 0;
    virtual bool fileExists(const std::string &path) = 0;
    virtual bool isRegularFile(const std::string &path) = 0;
    virtual bool isDirectory(const std::string &path) = 0;
#endif

    static IO *getInstance();
};

}

#endif //VANADIUM_IO_H
