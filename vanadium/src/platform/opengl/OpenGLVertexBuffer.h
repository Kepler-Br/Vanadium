#ifndef VANADIUM_OPENGLVERTEXBUFFER_H
#define VANADIUM_OPENGLVERTEXBUFFER_H

#include "OpenGLIncludes.h"
#include "../../render/VertexBuffer.h"
#include "../../core/Types.h"

namespace Vanadium
{

// Stolen from The Cherno. Check his youtube channel: https://www.youtube.com/user/TheChernoProject
class OpenGLVertexBuffer : public VertexBuffer
{
private:
    GLuint pointer;
    VNsize sizeInBytes;
    VertexBuffer::Layout layout;

public:
    OpenGLVertexBuffer(const void *data, VNsize size, VertexBuffer::Usage usage);
    ~OpenGLVertexBuffer();

    void *getRaw() const noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    void setData(const void *data, VNsize sizeInBytes) override;
    const VertexBuffer::Layout& getLayout() const override;
    void setLayout(const VertexBuffer::Layout &layout) override;

    static GLenum usageToOpenGLUsage(Usage usage);
};

}


#endif //VANADIUM_OPENGLVERTEXBUFFER_H
