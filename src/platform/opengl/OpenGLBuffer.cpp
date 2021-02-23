#include "OpenGLBuffer.h"
#include "../../core/Log.h"
#include "OpenGLCall.h"

namespace Vanadium
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, uint32_t sizeInBytes, VertexBufferSpecification specification):
    sizeInBytes(sizeInBytes)
{
    GLenum usage = OpenGLVertexBuffer::usageToOpenGLUsage(specification.usage);

    glGenBuffers(1, &this->pointer);
    glCall(glBufferData(this->pointer, sizeInBytes, data, usage));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    VAN_ENGINE_TRACE("Destroying VertexBuffer data.");
    glDeleteBuffers(1, &this->pointer);
}

void *OpenGLVertexBuffer::getRaw() const noexcept
{
    return (void *)&this->pointer;
}

void OpenGLVertexBuffer::bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, this->pointer);
}

void OpenGLVertexBuffer::unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::setData(const void *data, uint32_t sizeInBytes)
{
    VAN_ENGINE_TRACE("Updating VertexBuffer data.");
    if (sizeInBytes > this->sizeInBytes)
    {
        VAN_ENGINE_ERROR("OpenGLVertexBuffer::setData: New data size is greater that the original size.");
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, this->pointer);
    glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeInBytes, data));
}

GLenum OpenGLVertexBuffer::usageToOpenGLUsage(VertexBufferUsage usage)
{
    switch (usage)
    {
        case VertexBufferUsage::Static:
            return GL_STATIC_DRAW;
        case VertexBufferUsage::Dynamic:
            return GL_DYNAMIC_DRAW;
        case VertexBufferUsage::Stream:
            return GL_STREAM_DRAW;
        default:
            VAN_ENGINE_ERROR("OpenGLVertexBuffer::usageToOpenGLUsage: unknown VertexBufferUsage.");
            return GL_STATIC_DRAW;
    }
}

/*
 * OpenGLIndexBuffer
 */

OpenGLIndexBuffer::OpenGLIndexBuffer(const VNuint *indices, uint32_t size) :
        size(size)
{
    glGenBuffers(1, &this->pointer);
    glBindBuffer(GL_ARRAY_BUFFER, this->pointer);
    glCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(VNuint), indices, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    VAN_ENGINE_TRACE("Destroying IndexBuffer data.");
    glDeleteBuffers(1, &this->pointer);
}

void *OpenGLIndexBuffer::getRaw() const noexcept
{
    return (void *)&this->pointer;
}

void OpenGLIndexBuffer::bind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->pointer);
}

void OpenGLIndexBuffer::unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::getSize() const noexcept
{
    return this->size;
}
}