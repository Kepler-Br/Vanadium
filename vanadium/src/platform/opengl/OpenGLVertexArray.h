#ifndef VANADIUM_OPENGLVERTEXARRAY_H
#define VANADIUM_OPENGLVERTEXARRAY_H

#include <vector>

#include "../../render/VertexArray.h"
#include "../../core/Types.h"

namespace Vanadium
{

class OpenGLVertexArray : public VertexArray
{
private:
    std::vector<Ref<VertexBuffer>> vertexBuffers;
    Ref<IndexBuffer> indexBuffer;
    GLuint pointer;
    VNsize vertexBufferIndex;

    static GLenum dataTypeToOpenGLEnum(DataTypes type);

public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    void bind() const noexcept override;
    void unbind() const noexcept override;
    void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) noexcept override;
    void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) noexcept override;
    const Ref<IndexBuffer> &getIndexBuffer() const noexcept override;
    const std::vector<Ref<VertexBuffer>> &getVertexBuffers() const noexcept override;
    void *getRaw() const noexcept override;

};

}


#endif //VANADIUM_OPENGLVERTEXARRAY_H
