#ifndef VANADIUM_OPENGLBUFFER_H
#define VANADIUM_OPENGLBUFFER_H

#include "OpenGLIncludes.h"
#include "../../render/Buffer.h"
#include "../../core/Types.h"

namespace Vanadium
{

// Completely stolen from The Cherno. Check his youtube channel: https://www.youtube.com/user/TheChernoProject
class OpenGLVertexBuffer : public VertexBuffer
{
private:
    GLuint pointer;
    VNsize sizeInBytes;
    BufferLayout layout;

public:
    OpenGLVertexBuffer(const void *data, VNsize size, VertexBuffer::Usage usage);
    ~OpenGLVertexBuffer();

    void *getRaw() const noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    void setData(const void *data, VNsize sizeInBytes) override;
    const BufferLayout& getLayout() const override;
    void setLayout(const BufferLayout &layout) override;

    static GLenum usageToOpenGLUsage(Usage usage);
};

class OpenGLIndexBuffer : public IndexBuffer
{
private:
    GLuint pointer;
    VNsize size;

public:
    OpenGLIndexBuffer(const VNuint* indices, VNsize size);
    ~OpenGLIndexBuffer();

    void *getRaw() const noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    VNsize getCount() const noexcept override;
};

}


#endif //VANADIUM_OPENGLBUFFER_H
