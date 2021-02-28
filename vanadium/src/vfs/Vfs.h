#ifndef VANADIUM_VFS_H
#define VANADIUM_VFS_H

#include <string>
#include <vector>

#include <physfs.h>
#include <cstring>
#include "../core/Types.h"

// std::filesystem like.
namespace Vanadium
{

namespace Vfs
{

bool init(const std::string &workingDirectory);
bool isInit();
bool deinit();
std::string getError();
bool mount(const std::string &physicalPath, const std::string &mountPoint, int appendToPath = 1);
bool unmount(const std::string &physicalPath);
bool isDirectory(const std::string &path);
bool isRegularFile(const std::string &path);
VNsizei fileSize(const std::string &path);
bool exists(const std::string &path);
bool createDirectories(const std::string &path);
std::vector<std::string> listDirectory(const std::string &path);
// What?
std::vector<std::string> listSearchPath();

}

}

#endif //VANADIUM_VFS_H
