#ifndef VANADIUM_MESH_H
#define VANADIUM_MESH_H

#include "../core/Types.h"

namespace Vanadium
{
class VertexBuffer;
class VertexArray;
class IndexBuffer;

class Mesh
{
protected:
    Ref<VertexArray> vertexArray = nullptr;

public:
    Mesh() = default;
    explicit Mesh(Ref<VertexArray> &vertexArray);
    Mesh(const Ref<VertexBuffer> &vertexBuffer, const Ref<IndexBuffer> &indexBuffer);
    virtual ~Mesh() = default;

    void setVertexArray(Ref<VertexArray> &arr) noexcept;
    Ref<VertexArray> getVertexArray() noexcept;
    void bind() noexcept;
    bool operator!();
};
}

#endif //VANADIUM_MESH_H
