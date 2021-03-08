#include "OpenGLVertexArray.h"
#include "../../core/Log.h"
#include "../../core/Assert.h"
#include "../../render/IndexBuffer.h"
#include "OpenGLCall.h"

namespace Vanadium
{

GLenum OpenGLVertexArray::dataTypeToOpenGLEnum(DataTypes type)
{
    switch (type)
    {
        case DataTypes::Float:    //return GL_FLOAT;
        case DataTypes::Float2:   //return GL_FLOAT;
        case DataTypes::Float3:   //return GL_FLOAT;
        case DataTypes::Float4:   //return GL_FLOAT;
        case DataTypes::Mat3:     //return GL_FLOAT;
        case DataTypes::Mat4:     return GL_FLOAT;
        case DataTypes::Int:      //return GL_INT;
        case DataTypes::Int2:     //return GL_INT;
        case DataTypes::Int3:     //return GL_INT;
        case DataTypes::Int4:     return GL_INT;
        case DataTypes::Bool:     return GL_BOOL;
        default:
            VAN_ENGINE_ASSERT(false, "OpenGLVertexArray::dataTypeToOpenGLEnum: unknown data type!");
            return GL_INT;
    }
}

OpenGLVertexArray::OpenGLVertexArray()
{
//    VAN_ENGINE_TRACE("Creating OpenGLVertexArray.");
    glGenVertexArrays(1, &this->pointer);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
//    VAN_ENGINE_TRACE("Destroying OpenGLVertexArray.");
    glDeleteVertexArrays(1, &this->pointer);
}

void OpenGLVertexArray::bind() const noexcept
{
    glBindVertexArray(this->pointer);
}

void OpenGLVertexArray::unbind() const noexcept
{
    glBindVertexArray(0);
}

// Todo: Oh, my... Split this into pieces!
void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
{
    if (vertexBuffer->getLayout().getElements().empty())
    {
        VAN_ENGINE_ERROR("OpenGLVertexArray::addVertexBuffer Vertex Buffer has no layout!");
        return;
    }

    glBindVertexArray(this->pointer);
    vertexBuffer->bind();

    const auto& layout = vertexBuffer->getLayout();
    for (const auto& element : layout)
    {
        switch (element.type)
        {
            case DataTypes::Float:
            case DataTypes::Float2:
            case DataTypes::Float3:
            case DataTypes::Float4:
            {
                glEnableVertexAttribArray((GLuint)this->vertexBufferIndex);
                glVertexAttribPointer((GLuint)this->vertexBufferIndex,
                                      (GLint)element.getComponentCount(),
                                      OpenGLVertexArray::dataTypeToOpenGLEnum(element.type),
                                      (GLboolean)(element.normalized ? GL_TRUE : GL_FALSE),
                                      layout.getStride(),
                                      (const void*)element.offset);
                this->vertexBufferIndex++;
                break;
            }
            case DataTypes::Int:
            case DataTypes::Int2:
            case DataTypes::Int3:
            case DataTypes::Int4:
            case DataTypes::Bool:
            {
                glEnableVertexAttribArray((GLuint)this->vertexBufferIndex);
                glVertexAttribIPointer((GLuint)this->vertexBufferIndex,
                                       (GLuint)element.getComponentCount(),
                                       dataTypeToOpenGLEnum(element.type),
                                       layout.getStride(),
                                       (const void*)element.offset);
                this->vertexBufferIndex++;
                break;
            }
            case DataTypes::Mat3:
            case DataTypes::Mat4:
            {
                VNsize count = element.getComponentCount();
                for (VNsize i = 0; i < count; i++)
                {
                    glEnableVertexAttribArray(this->vertexBufferIndex);
                    glVertexAttribPointer(this->vertexBufferIndex,
                                          count,
                                          OpenGLVertexArray::dataTypeToOpenGLEnum(element.type),
                                          element.normalized ? GL_TRUE : GL_FALSE,
                                          layout.getStride(),
                                          (const void*)(element.offset + sizeof(VNfloat) * count * i));
                    glVertexAttribDivisor(this->vertexBufferIndex, 1);
                    this->vertexBufferIndex++;
                }
                break;
            }
            default:
                VAN_ENGINE_ASSERT(false, "OpenGLVertexArray::addVertexBuffer: Unknown data type!");
        }
    }

    this->vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) noexcept
{
    this->indexBuffer = indexBuffer;
    this->bind();
    this->indexBuffer->bind();
}

const Ref<IndexBuffer> &OpenGLVertexArray::getIndexBuffer() const noexcept
{
    if (!this->indexBuffer)
        VAN_ENGINE_ERROR("OpenGLVertexArray::getIndexBuffer: indexBuffer is nullptr!");
    return this->indexBuffer;
}

const std::vector<Ref<VertexBuffer>> &OpenGLVertexArray::getVertexBuffers() const noexcept
{
    return this->vertexBuffers;
}

void *OpenGLVertexArray::getRaw() const noexcept
{
    return (void *)&this->pointer;
}

bool OpenGLVertexArray::operator!() const noexcept
{
    return (this->pointer == 0) || (this->indexBuffer == nullptr) || (this->vertexBuffers.empty());
}

}