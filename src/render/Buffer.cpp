#include "Buffer.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLBuffer.h"
#elif defined(VANADIUM_RENDERAPI_OPENGLES)
    #error "Unsupported render api."
#elif defined(VANADIUM_RENDERAPI_VULKAN)
    #error "Unsupported render api."
#elif defined(VANADIUM_RENDERAPI_DIRECTX)
    #error "Unsupported render api."
#elif defined(VANADIUM_RENDERAPI_DIRECTX12)
    #error "Unsupported render api."
#else
    #error "Undefined render api."
#endif

namespace Vanadium
{

VertexBuffer *VertexBufferFactory::create(const std::vector<uint8_t> &data, VertexBufferSpecification specification)
{
    return VertexBufferFactory::create((void *)&data[0], data.size(), specification);
}

VertexBuffer *VertexBufferFactory::create(const void *data, uint32_t sizeInBytes, VertexBufferSpecification specification)
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return new OpenGLVertexBuffer(data, sizeInBytes, specification);
#elif defined(VANADIUM_RENDERAPI_OPENGLES)
    #error "OpenGLES is not yet supported."
#elif defined(VANADIUM_RENDERAPI_VULKAN)
    #error "Vulkan is not yet supported."
#elif defined(VANADIUM_RENDERAPI_DIRECTX)
    #error "DirectX is not yet supported."
#elif defined(VANADIUM_RENDERAPI_DIRECTX12)
    #error "DirectX 12 is not yet supported."
#else
    #error "Undefined render api."
#endif
}


IndexBuffer *IndexBufferFactory::create(const std::vector<VNuint> &data)
{
    return IndexBufferFactory::create(&data[0], data.size());
}

IndexBuffer *IndexBufferFactory::create(const VNuint *data, uint32_t count)
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return new OpenGLIndexBuffer(data, count);
#elif defined(VANADIUM_RENDERAPI_OPENGLES)
    #error "OpenGLES is not yet supported."
#elif defined(VANADIUM_RENDERAPI_VULKAN)
    #error "Vulkan is not yet supported."
#elif defined(VANADIUM_RENDERAPI_DIRECTX)
    #error "DirectX is not yet supported."
#elif defined(VANADIUM_RENDERAPI_DIRECTX12)
    #error "DirectX 12 is not yet supported."
#else
    #error "Undefined render api."
#endif
}


}