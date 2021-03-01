#include "FileStream.h"
#include "Exceptions.h"
#include <string>

namespace Vanadium
{

namespace Vfs
{

FileStream::FileStream(const std::string &path, OpenMode mode)
{
    this->open(path, mode);
}

FileStream::~FileStream()
{
    this->flush();
    this->close();
}

bool FileStream::open(const std::string &path, OpenMode mode)
{
    if (this->handle != nullptr)
        return false;
    if (mode == OpenMode::Append)
        this->handle = PHYSFS_openAppend(path.c_str());
    else if (mode == OpenMode::Output)
        this->handle = PHYSFS_openWrite(path.c_str());
    else if (mode == OpenMode::Input)
        this->handle = PHYSFS_openRead(path.c_str());
    else
    {
        this->isFileOpen = false;
        return false;
    }
    this->errorOccurred = this->handle == nullptr;
    if (this->errorOccurred)
        this->isFileOpen = false;
    this->isFileOpen = true;
    return this->errorOccurred;
}

bool FileStream::fail() const
{
    return this->errorOccurred;
}

bool FileStream::seek(VNsize pos) noexcept
{
    int resultStatus = PHYSFS_seek(this->handle, pos);

    if (resultStatus == 0)
        this->errorOccurred = true;
    return resultStatus != 0;
}

VNsizei FileStream::tell() noexcept
{
    if (this->errorOccurred)
        return -1;
    VNsizei position = PHYSFS_tell(this->handle);

    if (position == -1)
        this->errorOccurred = true;
    return position;
}

VNsizei FileStream::write(const void *buffer, VNsize length)
{
    if (this->errorOccurred)
        return -1;
    VNsizei wrote = PHYSFS_writeBytes(this->handle, buffer, length);

    if (wrote != length)
        this->errorOccurred = true;
    return wrote;
}

VNsizei FileStream::read(void *buffer, VNsize length)
{
    if (this->errorOccurred)
        return -1;
    VNsizei red = PHYSFS_readBytes(this->handle, buffer, length);

    if (red == -1)
        this->errorOccurred = true;
    return red;
}

VNsizei FileStream::length()
{
    if (this->errorOccurred)
        return -1;
    VNsizei result = PHYSFS_fileLength(this->handle);

    if (result == -1)
        this->errorOccurred = true;
    return result;
}

bool FileStream::eof() noexcept
{
    if (this->errorOccurred)
        return true;
    return PHYSFS_eof(this->handle) != 0;
}

bool FileStream::flush()
{
    if (this->errorOccurred)
        return false;
    if (!this->isFileOpen)
    {
        this->errorOccurred = true;
        return false;
    }
    int returnStatus = PHYSFS_flush(this->handle);

    if (returnStatus == 0)
    {
        this->errorOccurred = true;
        return false;
    }
    return true;
}

bool FileStream::close()
{
    if (!this->isFileOpen)
        return false;
    int returnStatus = PHYSFS_close(this->handle);

    if (returnStatus == 0)
    {
        this->errorOccurred = true;
        return false;
    }
    this->handle = nullptr;
    this->errorOccurred = false;
    this->isFileOpen = false;
    return true;
}

void FileStream::resetErrorFlag()
{
    this->errorOccurred = false;
}

bool FileStream::operator!() const
{
    return errorOccurred;
}

FileStream &FileStream::operator<<(const bool &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const short &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const unsigned short &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const int &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const unsigned int &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const long &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const unsigned long &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const long long int &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const unsigned long long int &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const char &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const unsigned char &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const std::string &arg)
{
    this->write((void*)arg.c_str(), arg.size() * sizeof(char));
    return *this;
}

FileStream &FileStream::operator<<(const float &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const double &arg)
{
    this->write((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator<<(const glm::ivec2 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg.x)*2);
    return *this;
}

FileStream &FileStream::operator<<(const glm::ivec3 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg.x)*3);
    return *this;
}

FileStream &FileStream::operator<<(const glm::ivec4 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg.x)*4);
    return *this;
}

FileStream &FileStream::operator<<(const glm::mat4 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg[0])*4*4);
    return *this;
}

FileStream &FileStream::operator<<(const glm::mat3 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg[0])*3*3);
    return *this;
}

FileStream &FileStream::operator<<(const glm::mat2 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg[0])*2*2);
    return *this;
}

FileStream &FileStream::operator<<(const glm::vec4 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg.x)*4);
    return *this;
}

FileStream &FileStream::operator<<(const glm::vec3 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg.x)*3);
    return *this;
}

FileStream &FileStream::operator<<(const glm::vec2 &arg)
{
    this->write((void*)glm::value_ptr(arg), sizeof(arg.x)*2);
    return *this;
}

/*
 * Write operations.
 */

FileStream &FileStream::operator>>(bool &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(short &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(unsigned short &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(int &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(unsigned int &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(long &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(unsigned long &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(long long int &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(unsigned long long int &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(char &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(unsigned char &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(float &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(double &arg)
{
    this->read((void*)&arg, sizeof(arg));
    return *this;
}

FileStream &FileStream::operator>>(glm::ivec2 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg.x)*2);
    return *this;
}

FileStream &FileStream::operator>>(glm::ivec3 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg.x)*3);
    return *this;
}

FileStream &FileStream::operator>>(glm::ivec4 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg.x)*4);
    return *this;
}

FileStream &FileStream::operator>>(glm::mat4 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg[0])*4*4);
    return *this;
}

FileStream &FileStream::operator>>(glm::mat3 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg[0])*3*3);
    return *this;
}

FileStream &FileStream::operator>>(glm::mat2 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg[0])*2*2);
    return *this;
}

FileStream &FileStream::operator>>(glm::vec4 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg.x)*4);
    return *this;
}

FileStream &FileStream::operator>>(glm::vec3 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg.x)*3);
    return *this;
}

FileStream &FileStream::operator>>(glm::vec2 &arg)
{
    this->read((void*)glm::value_ptr(arg), sizeof(arg.x)*2);
    return *this;
}
}

}