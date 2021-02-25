#include "Buffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLBuffer.h"
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
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return MakeRef<OpenGLVertexBuffer>(data, sizeInBytes, usage);
#else
    #error "Unsupported render API."
#endif
}


Ref<IndexBuffer> IndexBufferFactory::create(const std::vector<VNuint> &data)
{
    return IndexBufferFactory::create(&data[0], data.size());
}

Ref<IndexBuffer> IndexBufferFactory::create(const VNuint *data, VNsize count)
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return MakeRef<OpenGLIndexBuffer>(data, count);
#else
    #error "Unsupported render API."
#endif
}


}