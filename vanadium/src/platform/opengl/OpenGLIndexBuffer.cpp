#include "OpenGLIndexBuffer.h"
#include "../../core/Log.h"
#include "OpenGLCall.h"

namespace Vanadium
{

OpenGLIndexBuffer::OpenGLIndexBuffer(const VNuint *indices, VNsize size) :
        size(size)
{
//    VAN_ENGINE_TRACE("Generating IndexBuffer.");
    glGenBuffers(1, &this->pointer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->pointer);
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * (VNsize)sizeof(VNuint), indices, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
//    VAN_ENGINE_TRACE("Destroying IndexBuffer data.");
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

bool OpenGLIndexBuffer::operator!() const noexcept
{
    return (this->pointer == 0) || (this->size == 0);
}

}