#ifndef VANADIUM_VERTEXARRAY_H
#define VANADIUM_VERTEXARRAY_H

#include <vector>
#include "../core/Types.h"

#include "VertexBuffer.h"

namespace Vanadium
{

class IndexBuffer;

class VertexArray
{
public:
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) noexcept = 0;
    virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) noexcept = 0;
    virtual const Ref<IndexBuffer> &getIndexBuffer() const noexcept= 0;
    virtual const std::vector<Ref<VertexBuffer>> &getVertexBuffers() const noexcept= 0;
    virtual void *getRaw() const noexcept = 0;
};

class VertexArrayFactory
{
public:
    static Ref<VertexArray> create();
};

}


#endif //VANADIUM_VERTEXARRAY_H
