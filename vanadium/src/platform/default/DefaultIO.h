#ifndef VANADIUM_DEFAULTIO_H
#define VANADIUM_DEFAULTIO_H

#include "../../core/IO.h"
#include <fstream>

namespace Vanadium
{

class DefaultIO : public IO
{
private:
    bool isFail = false;

public:
#if __cplusplus >= 201703L
    bool fail() noexcept override;
    std::vector<char> readFile(const std::string &path) noexcept override;
    void writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite) noexcept override;
    std::vector<std::string> listDirectory(const std::string &path) noexcept override;
    void removeAll(const std::string &path) noexcept override;
    void remove(const std::string &path) noexcept override;
    void createFile(const std::string &path) noexcept override;
    void makeDir(const std::string &path) noexcept override;
    void makeDirs(const std::string &path) noexcept override;
    VNsize fileSize(const std::string &path) noexcept override;
    bool fileExists(const std::string &path) noexcept override;
    bool isRegularFile(const std::string &path) noexcept override;
    bool isDirectory(const std::string &path) noexcept override;
#else
#warning "DefaultIO implementation in current C++(< C++17) standard may throw exceptions!"
    bool fail() override;
    std::vector<char> readFile(const std::string &path) override;
    void writeFile(const std::string &path, void *data, VNsize dataSize, bool overwrite) override;
    std::vector<std::string> listDirectory(const std::string &path) override;
    void removeAll(const std::string &path) override;
    void remove(const std::string &path) override;
    void createFile(const std::string &path) override;
    void makeDir(const std::string &path) override;
    void makeDirs(const std::string &path) override;
    VNsize fileSize(const std::string &path) override;
    bool fileExists(const std::string &path) override;
    bool isRegularFile(const std::string &path) override;
    bool isDirectory(const std::string &path) override;
#endif

};

}

#endif //VANADIUM_DEFAULTIO_H
