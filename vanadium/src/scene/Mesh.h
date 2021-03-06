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

class MeshFactory
{
public:
    static Ref<Mesh> plane(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight);
    static Ref<Mesh> unitPlane(VNfloat multiplication = 1.0f);
    static Ref<Mesh> unitCube(VNfloat multiplication = 1.0f);
    static Ref<Mesh> fromVertices(VNfloat *data, VNsize size);
    static Ref<Mesh> fromVerticesIndices(VNfloat *vertices, VNsize vertexCount, VNuint *indices, VNsize indicesCount);

};


}

#endif //VANADIUM_MESH_H
