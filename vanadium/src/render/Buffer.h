#ifndef VANADIUM_BUFFER_H
#define VANADIUM_BUFFER_H

#include <cstdint>
#include <utility>
#include <vector>
#include "../core/Types.h"
#include "../core/Assert.h"

namespace Vanadium
{

struct BufferElement
{
    std::string name;
    DataTypes type;
    VNsize size;
    VNsize offset;
    bool normalized;

    BufferElement() = default;

    BufferElement(DataTypes type, std::string name, bool normalized = false)
            : name(std::move(name)), type(type), size(dataTypeToSize(type)), offset(0), normalized(normalized)
    {
    }

    VNsize getComponentCount() const
    {
        switch (this->type)
        {
            case DataTypes::Float:   return 1;
            case DataTypes::Float2:  return 2;
            case DataTypes::Float3:  return 3;
            case DataTypes::Float4:  return 4;
            case DataTypes::Mat3:    return 3; // 3* float3
            case DataTypes::Mat4:    return 4; // 4* float4
            case DataTypes::Int:     return 1;
            case DataTypes::Int2:    return 2;
            case DataTypes::Int3:    return 3;
            case DataTypes::Int4:    return 4;
            case DataTypes::Bool:    return 1;
            default: VAN_ENGINE_ASSERT(false, "Unknown ShaderDataType!"); return 0;
        }
    }
};

class BufferLayout
{
private:
    std::vector<BufferElement> elements;
    VNsize stride = 0;

public:
    BufferLayout() = default;

    BufferLayout(std::initializer_list<BufferElement> elements)
            : elements(elements)
    {
        calculateOffsetsAndStride();
    }

    uint32_t getStride() const { return this->stride; }
    const std::vector<BufferElement>& getElements() const { return this->elements; }

    std::vector<BufferElement>::iterator begin() { return this->elements.begin(); }
    std::vector<BufferElement>::iterator end() { return this->elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return this->elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return this->elements.end(); }

private:
    void calculateOffsetsAndStride()
    {
        size_t offset = 0;
        this->stride = 0;
        for (auto& element : this->elements)
        {
            element.offset = offset;
            offset += element.size;
            this->stride += element.size;
        }
    }
};

class VertexBuffer
{
public:
    enum class Usage
    {
        Static = 0,
        Dynamic,
        Stream
    };

public:
    virtual void *getRaw() const noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual void setData(const void *data, VNsize size) = 0;
    virtual const BufferLayout& getLayout() const = 0;
    virtual void setLayout(const BufferLayout &layout) = 0;
};

class VertexBufferFactory
{
public:
    static Ref<VertexBuffer> create(VNsize sizeInBytes, VertexBuffer::Usage usage = VertexBuffer::Usage::Static);
    static Ref<VertexBuffer> create(const std::vector<int8_t> &data, VertexBuffer::Usage usage = VertexBuffer::Usage::Static);
    static Ref<VertexBuffer> create(const void *data, VNsize sizeInBytes, VertexBuffer::Usage usage = VertexBuffer::Usage::Static);
};

class IndexBuffer
{
public:
    virtual void *getRaw() const noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual VNsize getSize() const noexcept = 0;
};

class IndexBufferFactory
{
public:
    static Ref<IndexBuffer> create(const std::vector<VNuint> &data);
    static Ref<IndexBuffer> create(const VNuint *data, VNsize count);
};

}
#endif //VANADIUM_BUFFER_H
