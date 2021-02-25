#include "Buffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLBuffer.h"
    using VertexBufferImpl = Vanadium::OpenGLVertexBuffer;
    using IndexBufferImpl = Vanadium::OpenGLIndexBuffer;
#endif

namespace Vanadium
{

Ref<VertexBuffer> VertexBufferFactory::create(VNsize sizeInBytes, VertexBuffer::Usage usage)
{
    return VertexBufferFactory::create(nullptr, sizeInBytes, usage);
}

Ref<VertexBuffer> VertexBufferFactory::create(const std::vector<int8_t> &data, VertexBuffer::Usage usage)
{
    return VertexBufferFactory::create((void *)&data[0], data.size(), usage);
}

Ref<VertexBuffer> VertexBufferFactory::create(const void *data, VNsize sizeInBytes, VertexBuffer::Usage usage)
{
    return MakeRef<VertexBufferImpl>(data, sizeInBytes, usage);
}

/*
 * IndexBufferFactory.
 */

Ref<IndexBuffer> IndexBufferFactory::create(const std::vector<VNuint> &data)
{
    return IndexBufferFactory::create(&data[0], data.size());
}

Ref<IndexBuffer> IndexBufferFactory::create(const VNuint *data, VNsize count)
{
    return MakeRef<IndexBufferImpl>(data, count);
}


}