#include "OpenGLBuffer.h"
#include "../../core/Log.h"
#include "OpenGLCall.h"
#include "../../core/Assert.h"

namespace Vanadium
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, VNsize sizeInBytes, VertexBuffer::Usage usage):
    sizeInBytes(sizeInBytes)
{
    GLenum GLUsage = OpenGLVertexBuffer::usageToOpenGLUsage(usage);

    VAN_ENGINE_TRACE("Generating VertexBuffer.");
    glGenBuffers(1, &this->pointer);
    glBindBuffer(GL_ARRAY_BUFFER, this->pointer);
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GLUsage));
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

void OpenGLVertexBuffer::setData(const void *data, VNsize sizeInBytes)
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

const BufferLayout& OpenGLVertexBuffer::getLayout() const
{
    return this->layout;
}

void OpenGLVertexBuffer::setLayout(const BufferLayout &layout)
{
    this->layout = layout;
}

GLenum OpenGLVertexBuffer::usageToOpenGLUsage(Usage usage)
{
    switch (usage)
    {
        case Usage::Static:
            return GL_STATIC_DRAW;
        case Usage::Dynamic:
            return GL_DYNAMIC_DRAW;
        case Usage::Stream:
            return GL_STREAM_DRAW;
        default:
            VAN_ENGINE_ASSERT(false, "OpenGLVertexBuffer::usageToOpenGLUsage: unknown VertexBufferUsage.");
            return GL_STATIC_DRAW;
    }
}

/*
 * OpenGLIndexBuffer
 */

OpenGLIndexBuffer::OpenGLIndexBuffer(const VNuint *indices, VNsize size) :
        size(size)
{
    VAN_ENGINE_TRACE("Generating IndexBuffer.");
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

VNsize OpenGLIndexBuffer::getCount() const noexcept
{
    return this->size;
}

}