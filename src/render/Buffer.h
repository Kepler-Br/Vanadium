#ifndef VANADIUM_BUFFER_H
#define VANADIUM_BUFFER_H

#include <cstdint>
#include <vector>
#include "../core/Types.h"

namespace Vanadium
{

enum class DataTypes
{
    Float = 0,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

enum class VertexBufferUsage
{
    Static = 0,
    Dynamic,
    Stream
};

struct VertexBufferSpecification
{
    DataTypes dataType;
    VertexBufferUsage usage = VertexBufferUsage::Static;
};

class VertexBuffer
{
public:
    virtual void *getRaw() const noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual void setData(const void *data, uint32_t size) = 0;
};

class VertexBufferFactory
{
public:
    static VertexBuffer *create(const std::vector<uint8_t> &data, VertexBufferSpecification specification);
    static VertexBuffer *create(const void *data, uint32_t sizeInBytes, VertexBufferSpecification specification);
};

class IndexBuffer
{
public:
    virtual void *getRaw() const noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual uint32_t getSize() const noexcept = 0;
};

class IndexBufferFactory
{
public:
    static IndexBuffer *create(const std::vector<VNuint> &data);
    static IndexBuffer *create(const VNuint *data, uint32_t count);
};

}
#endif //VANADIUM_BUFFER_H
