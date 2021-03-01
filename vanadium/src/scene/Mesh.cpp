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

}
