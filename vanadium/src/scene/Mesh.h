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
public:
    enum class PrimitiveType
    {
        Lines = 0,
        LineLoop,
        Triangles,
    };

protected:
    Ref<VertexArray> vertexArray = nullptr;
    PrimitiveType primitiveType;

public:
    explicit Mesh(PrimitiveType targetPrimitiveType):
        primitiveType(targetPrimitiveType)
    {}
    Mesh(const Ref<VertexArray> &vertexArray, PrimitiveType targetPrimitiveType);
    Mesh(const Ref<VertexBuffer> &vertexBuffer, const Ref<IndexBuffer> &indexBuffer, PrimitiveType targetPrimitiveType);
    virtual ~Mesh() = default;

    void setVertexArray(const Ref<VertexArray> &arr) noexcept;
    Ref<VertexArray> getVertexArray() noexcept;
    PrimitiveType getPrimitiveType() noexcept;
    void setPrimitiveType(PrimitiveType targetPrimitiveType) noexcept;
    void bind() noexcept;
    void unbind() noexcept;
    bool operator!();
};

class MeshFactory
{
public:
    static Ref<Mesh> wireframePlane(glm::vec2 bottomLeft, glm::vec2 bottomRight, glm::vec2 topLeft, glm::vec2 topRight);
    static Ref<Mesh> unitWireframePlane(VNfloat multiplication = 1.0f);
    static Ref<Mesh> plane(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight);
    static Ref<Mesh> unitPlane(VNfloat multiplication = 1.0f);
    static Ref<Mesh> unitCube(VNfloat multiplication = 1.0f);
    static Ref<Mesh> grid(VNfloat size, VNfloat step);
    static Ref<Mesh> fromVertices(VNfloat *data, VNsize size, Mesh::PrimitiveType targetPrimitiveType);
    static Ref<Mesh> fromVerticesIndices(VNfloat *vertices, VNsize vertexCount, VNuint *indices, VNsize indicesCount, Mesh::PrimitiveType targetPrimitiveType);

};


}

#endif //VANADIUM_MESH_H
