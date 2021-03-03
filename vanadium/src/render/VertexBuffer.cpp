#include "VertexBuffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLVertexBuffer.h"
    using VertexBufferImpl = Vanadium::OpenGLVertexBuffer;
#endif

namespace Vanadium
{

Ref<VertexBuffer> VertexBufferFactory::create(VNsize sizeInBytes, VertexBuffer::Usage usage)
{
    return VertexBufferFactory::create(nullptr, sizeInBytes, usage);
}

Ref<VertexBuffer> VertexBufferFactory::create(const void *data, VNsize sizeInBytes, VertexBuffer::Usage usage)
{
    return MakeRef<VertexBufferImpl>(data, sizeInBytes, usage);
}

Ref<VertexBuffer> VertexBufferFactory::create(const std::vector<VNfloat> &vertices, VertexBuffer::Usage usage)
{
    return MakeRef<VertexBufferImpl>(&vertices[0], vertices.size(), usage);
}

}