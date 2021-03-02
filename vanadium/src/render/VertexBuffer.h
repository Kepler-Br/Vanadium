#ifndef VANADIUM_VERTEXBUFFER_H
#define VANADIUM_VERTEXBUFFER_H

#include <cstdint>
#include <utility>
#include <vector>
#include "../core/Types.h"
#include "../core/Assert.h"

namespace Vanadium
{

// See TheCherno.
class VertexBuffer
{
public:
    enum class Usage
    {
        Static = 0,
        Dynamic,
        Stream
    };

    struct Element
    {
        std::string name;
        DataTypes type;
        VNsize size;
        VNsize offset;
        bool normalized;

//        Element() = default;

        Element(DataTypes type, std::string name, bool normalized = false)
                : name(std::move(name)), type(type), size(dataTypeToSize(type)), offset(0), normalized(normalized)
        {
        }

        [[nodiscard]]
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

    class Layout
    {
    private:
        std::vector<Element> elements;
        VNsize stride = 0;

    public:
        Layout() = default;

        Layout(std::initializer_list<Element> elements)
                : elements(elements)
        {
            calculateOffsetsAndStride();
        }

        [[nodiscard]]
        VNsize getStride() const { return this->stride; }
        [[nodiscard]]
        const std::vector<Element>& getElements() const { return this->elements; }

        [[nodiscard]]
        std::vector<Element>::iterator begin() { return this->elements.begin(); }
        [[nodiscard]]
        std::vector<Element>::iterator end() { return this->elements.end(); }
        [[nodiscard]]
        std::vector<Element>::const_iterator begin() const { return this->elements.begin(); }
        [[nodiscard]]
        std::vector<Element>::const_iterator end() const { return this->elements.end(); }

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

public:
    [[nodiscard]]
    virtual void *getRaw() const noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual void setData(const void *data, VNsize size) = 0;
    [[nodiscard]]
    virtual const Layout& getLayout() const = 0;
    virtual void setLayout(const Layout &layout) = 0;
    virtual bool operator!() const noexcept = 0;
};

class VertexBufferFactory
{
public:
    static Ref<VertexBuffer> create(VNsize sizeInBytes, VertexBuffer::Usage usage = VertexBuffer::Usage::Static);
//    static Ref<VertexBuffer> create(const std::vector<int8_t> &data, VertexBuffer::Usage usage = VertexBuffer::Usage::Static);
    static Ref<VertexBuffer> create(const void *data, VNsize sizeInBytes, VertexBuffer::Usage usage = VertexBuffer::Usage::Static);
};



}
#endif //VANADIUM_VERTEXBUFFER_H
