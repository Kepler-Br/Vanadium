#ifndef VANADIUM_OPENGLINDEXBUFFER_H
#define VANADIUM_OPENGLINDEXBUFFER_H

#include "../../core/Types.h"
#include "../../render/IndexBuffer.h"

namespace Vanadium
{

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


#endif //VANADIUM_OPENGLINDEXBUFFER_H
