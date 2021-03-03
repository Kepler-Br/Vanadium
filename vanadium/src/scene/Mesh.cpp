#include "Mesh.h"
#include "../render/VertexBuffer.h"
#include "../render/VertexArray.h"
#include "../render/IndexBuffer.h"
#include "../core/Log.h"

namespace Vanadium
{

Mesh::Mesh(Ref<VertexArray> &vertexArray) :
        vertexArray(vertexArray)
{
    if (!this->vertexArray)
    {
        VAN_ENGINE_ERROR("Mesh::Mesh: vertexArray is nullptr.");
    }
}

Mesh::Mesh(const Ref<VertexBuffer> &vertexBuffer, const Ref<IndexBuffer> &indexBuffer)
{
    if (!vertexBuffer || !indexBuffer)
    {
        VAN_ENGINE_ERROR("Mesh::Mesh: vertexBuffer or indexBuffer is nullptr.");
        return;
    }
    this->vertexArray = VertexArrayFactory::create();
    this->vertexArray->addVertexBuffer(vertexBuffer);
    this->vertexArray->setIndexBuffer(indexBuffer);
    if (!this->vertexArray)
    {
        VAN_ENGINE_ERROR("Mesh::Mesh: created vertexArray is nullptr.");
    }
}

void Mesh::setVertexArray(Ref<VertexArray> &arr) noexcept
{
    if (arr != nullptr)
        this->vertexArray = arr;
}

Ref<VertexArray> Mesh::getVertexArray() noexcept
{
    return this->vertexArray;
}

void Mesh::bind() noexcept
{
    if (this->vertexArray)
        this->vertexArray->bind();
    else
        VAN_ENGINE_ERROR("Mesh::bind: this->vertexArray is nullptr.");
}

bool Mesh::operator!()
{
    if (this->vertexArray == nullptr || !(*this->vertexArray))
        return true;
    return false;
}

/*
 * Mesh factory.
 */

Ref<Mesh> MeshFactory::plane(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight)
{
    VNfloat one = 1.0f;
    // Float4 vboData, Float2 UV, Float3 normals.
    std::vector<VNfloat> vboData = {
            bottomLeft.x,  bottomLeft.y,  bottomLeft.z,  1.0f, one,  one,  0.0f, 0.0f, one,
            bottomRight.x, bottomRight.y, bottomRight.z, 1.0f, one,  0.0f, 0.0f, 0.0f, one,
            topRight.x,    topRight.y,    topRight.z,    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, one,
            topLeft.x,     topLeft.y,     topLeft.z,     1.0f, 0.0f, one,  0.0f, 0.0f, one,
    };
    Ref<VertexBuffer> vbo = VertexBufferFactory::create(&vboData[0], vboData.size() * sizeof(VNfloat));
    vbo->setLayout({{DataTypes::Float4, "Position"},
                    {DataTypes::Float2, "UV"},
                    {DataTypes::Float3, "Normal"}});
    Ref<IndexBuffer>  ibo = IndexBufferFactory::create({2, 1, 0, 3, 2, 0});
    Ref<VertexArray>  vao = VertexArrayFactory::create();
    vao->setIndexBuffer(ibo);
    vao->addVertexBuffer(vbo);
    vao->unbind();
    return MakeRef<Mesh>(vao);
}

Ref<Mesh> MeshFactory::unitPlane(VNfloat multiplication)
{
    VNfloat half = 0.5f * multiplication;
    return MeshFactory::plane({half, half, 0.0f},
                              {half, -half, 0.0f},
                              {-half, half, 0.0f},
                              {-half, -half, 0.0f});
}

Ref<Mesh> MeshFactory::unitCube(VNfloat multiplication)
{
    VNfloat half = 0.5f * multiplication;
    VNfloat offset = half;
    VNfloat one = 1.0f;

    std::vector<VNfloat> vertices = {
                                    // front
                                    -half, -half, offset, 1.0f,
                                    -half,  half, offset, 1.0f,
                                     half, -half, offset, 1.0f,
                                     half,  half, offset, 1.0f,
                                    // back
                                    -half, -half, -offset, 1.0f,
                                    -half,  half, -offset, 1.0f,
                                     half, -half, -offset, 1.0f,
                                     half,  half, -offset, 1.0f,
                                    // left
                                    -half, offset, -half, 1.0f,
                                    -half, offset,  half, 1.0f,
                                     half, offset, -half, 1.0f,
                                     half, offset,  half, 1.0f,
                                    // right
                                    -half, -offset, -half, 1.0f,
                                    -half, -offset,  half, 1.0f,
                                     half, -offset, -half, 1.0f,
                                     half, -offset,  half, 1.0f,
                                    // bottom
                                    offset, -half, -half, 1.0f,
                                    offset, -half,  half, 1.0f,
                                    offset,  half, -half, 1.0f,
                                    offset,  half,  half, 1.0f,
                                     // up
                                    -offset, -half, -half, 1.0f,
                                    -offset, -half,  half, 1.0f,
                                    -offset,  half, -half, 1.0f,
                                    -offset,  half,  half, 1.0f,
    };

    std::vector<VNfloat> uvs = {
            // front
            0.0f, 0.0f,
            one, 0.0f,
            0.0f, one,
            one, one,
            // back
            0.0f, 0.0f,
            one, 0.0f,
            0.0f, one,
            one, one,
            // left
            0.0f, 0.0f,
            one, 0.0f,
            0.0f, one,
            one, one,
            // right
            0.0f, 0.0f,
            one, 0.0f,
            0.0f, one,
            one, one,
            // bottom
            0.0f, 0.0f,
            one, 0.0f,
            0.0f, one,
            one, one,
            // up
            0.0f, 0.0f,
            one, 0.0f,
            0.0f, one,
            one, one,
    };

    std::vector<VNfloat> normals = {
            // front
            0.0f, 0.0f, one,
            0.0f, 0.0f, one,
            0.0f, 0.0f, one,
            0.0f, 0.0f, one,
            // back
            0.0f, 0.0f, -one,
            0.0f, 0.0f, -one,
            0.0f, 0.0f, -one,
            0.0f, 0.0f, -one,
            // left
            0.0f, one, 0.0f,
            0.0f, one, 0.0f,
            0.0f, one, 0.0f,
            0.0f, one, 0.0f,
            // right
            0.0f, -one, 0.0f,
            0.0f, -one, 0.0f,
            0.0f, -one, 0.0f,
            0.0f, -one, 0.0f,
            // bottom
            one, 0.0f, 0.0f,
            one, 0.0f, 0.0f,
            one, 0.0f, 0.0f,
            one, 0.0f, 0.0f,
            // up
            -one, 0.0f, 0.0f,
            -one, 0.0f, 0.0f,
            -one, 0.0f, 0.0f,
            -one, 0.0f, 0.0f,
    };

    Ref<VertexBuffer> vbo = VertexBufferFactory::create(&vertices[0], vertices.size() * sizeof(VNfloat));
    vbo->setLayout({{DataTypes::Float4, "a_Position"}});

    Ref<VertexBuffer> uvBO = VertexBufferFactory::create(&uvs[0], uvs.size() * sizeof(VNfloat));
    uvBO->setLayout({{DataTypes::Float2, "a_UV"}});

    Ref<VertexBuffer> normalBO = VertexBufferFactory::create(&normals[0], normals.size() * sizeof(VNfloat));
    normalBO->setLayout({{DataTypes::Float3, "a_Normal"}});

    VNuint iboOffset = 4;
    Ref<IndexBuffer>  ibo = IndexBufferFactory::create({
                   2,             1,             0,             1,             2,             3,
       iboOffset+  0, iboOffset+  1, iboOffset+  2, iboOffset+  3, iboOffset+  2, iboOffset+  1,
       iboOffset*2+0, iboOffset*2+1, iboOffset*2+2, iboOffset*2+3, iboOffset*2+2, iboOffset*2+1,
       iboOffset*3+2, iboOffset*3+1, iboOffset*3+0, iboOffset*3+1, iboOffset*3+2, iboOffset*3+3,
       iboOffset*4+2, iboOffset*4+1, iboOffset*4+0, iboOffset*4+1, iboOffset*4+2, iboOffset*4+3,
       iboOffset*5+0, iboOffset*5+1, iboOffset*5+2, iboOffset*5+3, iboOffset*5+2, iboOffset*5+1,
    });
    Ref<VertexArray> vao = VertexArrayFactory::create();
    vao->addVertexBuffer(vbo);
    vao->addVertexBuffer(uvBO);
    vao->addVertexBuffer(normalBO);
    vao->setIndexBuffer(ibo);
    vao->unbind();
    return MakeRef<Mesh>(vao);
}

}
