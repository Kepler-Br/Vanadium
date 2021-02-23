#ifndef VANADIUM_OPENGLBUFFER_H
#define VANADIUM_OPENGLBUFFER_H

#include "OpenGLIncludes.h"
#include "../../render/Buffer.h"

namespace Vanadium
{

class OpenGLVertexBuffer : public VertexBuffer
{
private:
    GLuint pointer;
    uint32_t sizeInBytes;

public:
    OpenGLVertexBuffer(const void *data, uint32_t size, VertexBufferSpecification specification);
    ~OpenGLVertexBuffer();

    void *getRaw() const noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    void setData(const void *data, uint32_t sizeInBytes) override;

    static GLenum usageToOpenGLUsage(VertexBufferUsage usage);
};

class OpenGLIndexBuffer : public IndexBuffer
{
private:
    GLuint pointer;
    uint32_t size;

public:
    OpenGLIndexBuffer(const VNuint* indices, uint32_t size);
    ~OpenGLIndexBuffer();

    void *getRaw() const noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    uint32_t getSize() const noexcept override;
};

}


#endif //VANADIUM_OPENGLBUFFER_H
