#include "Vfs.h"
#include "Exceptions.h"
#include "FileStream.h"
#include <sstream>
#include "../core/Log.h"

namespace Vanadium
{

namespace Vfs
{

bool init(const std::string &workingDirectory)
{
    int returnStatus;
    if (PHYSFS_isInit() != 0)
        return true;
    if (workingDirectory.empty())
        returnStatus = PHYSFS_init(nullptr);
    else
        returnStatus = PHYSFS_init(workingDirectory.c_str());
    if (returnStatus == 0)
        return false;
    return true;
}
// PhysFS and Vanadium VFS errors are interchangeable.
ErrorCode getErrorCode()
{
    return (ErrorCode)PHYSFS_getLastErrorCode();
}

std::string errorCodeToString(ErrorCode code)
{
    return std::string(PHYSFS_getErrorByCode((PHYSFS_ErrorCode)code));
}

std::string getError()
{
    PHYSFS_ErrorCode errorCode = PHYSFS_getLastErrorCode();
    const char *errorMessage = PHYSFS_getErrorByCode(errorCode);
    return std::string(errorMessage);
}

void discardErrors()
{
    PHYSFS_getLastErrorCode();
}

std::vector<char> readWhole(const std::string &path)
{
    std::vector<char> data;
    FileStream file(path);
    VNsizei fileSize = file.length();

    if(!file)
        return data;
    data.resize(fileSize);
    fileSize = file.read(&data[0], fileSize);
    if (fileSize < 0)
    {
        return std::vector<char>();
    }
    data.resize(fileSize);
    return data;
}

bool isInit()
{
    return PHYSFS_isInit() != 0;
}

bool deinit()
{
    return PHYSFS_deinit() != 0;
}

bool mount(const std::string &physicalPath, const std::string &mountPoint, int appendToPath)
{
    int result = PHYSFS_mount(physicalPath.c_str(), mountPoint.c_str(), appendToPath) != 0;
    return result;
}

bool unmount(const std::string &physicalPath)
{
    return PHYSFS_unmount(physicalPath.c_str()) != 0;
}

bool isDirectory(const std::string &path)
{
    PHYSFS_Stat stat;
    int result = PHYSFS_stat(path.c_str(), &stat);

    if (result == 0)
        return false;
    if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY)
        return true;
    return false;
}

bool isRegularFile(const std::string &path)
{
    PHYSFS_Stat stat;
    int result = PHYSFS_stat(path.c_str(), &stat);

    if (result == 0)
        return false;
    if (stat.filetype == PHYSFS_FILETYPE_REGULAR)
        return true;
    return false;
}

bool isReadonly(const std::string &path)
{
    PHYSFS_Stat stat;
    int result = PHYSFS_stat(path.c_str(), &stat);

    if (result == 0)
        return false;
    return stat.readonly;
}

VNsizei fileSize(const std::string &path)
{
    PHYSFS_Stat stat;
    int result = PHYSFS_stat(path.c_str(), &stat);

    if (result == 0)
        return 0;
    return stat.filesize;
}

bool exists(const std::string &path)
{
    return PHYSFS_exists(path.c_str());
}

bool createDirectories(const std::string &path)
{
    return PHYSFS_mkdir(path.c_str()) != 0;
}

bool deleteFile(const std::string &path)
{
    return PHYSFS_delete(path.c_str()) != 0;
}

std::vector<std::string> listDirectory(const std::string &path)
{
    std::vector<std::string> fileList;
    char **rc = PHYSFS_enumerateFiles(path.c_str());
    char **i;

    for (i = rc; *i != nullptr; i++)
        fileList.emplace_back(*i);
    PHYSFS_freeList(rc);
    return fileList;
}

std::vector<std::string> listSearchPath()
{
    std::vector<std::string> searchPathList;
    char **i;

    for (i = PHYSFS_getSearchPath(); *i != nullptr; i++)
        searchPathList.emplace_back(*i);
    PHYSFS_freeList(i);
    return searchPathList;
}

}

}