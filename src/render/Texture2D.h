#ifndef VANADIUM_TEXTURE2D_H
#define VANADIUM_TEXTURE2D_H

#include <glm/vec2.hpp>
#warning "Implement Texture2D factory."

namespace Vanadium
{

enum class TextureColorFormat
{
    RGB = 0,
    RGBA,
    BGR,
    BGRA,
    Red,
    Depth,
    StencilIndex,
    DepthStencil,
};

enum class TextureDataFormat
{
    UnsignedByte = 0,
    Byte
};

enum class TextureFiltering
{
    Linear = 0,
    Nearest,
};

enum class TextureWrapping
{
    Repeat = 0,
    Clamp,
    Mirror,
};

struct TextureSpecification
{
    uint32_t width;
    uint32_t height;
    TextureColorFormat colorFormat = TextureColorFormat::RGB;
    TextureColorFormat internalFormat = TextureColorFormat::BGR;
    TextureDataFormat dataFormat = TextureDataFormat::UnsignedByte;
    TextureFiltering magnificationFilter = TextureFiltering::Nearest;
    TextureFiltering minificationFilter = TextureFiltering::Nearest;
    TextureWrapping wrapping = TextureWrapping::Repeat;
};

class Texture2D
{
public:
    virtual uint32_t getWidth() const noexcept = 0;
    virtual uint32_t getHeight() const noexcept = 0;
    virtual glm::ivec2 getGeometry() const noexcept = 0;
    virtual void destroy() noexcept = 0;
    virtual void resize(const glm::ivec2 &newGeometry) = 0;
    virtual void resize(uint32_t newWidth, uint32_t newHeight) = 0;
    virtual void setData(void* data, uint32_t size) noexcept = 0;
    virtual TextureSpecification getSpecification() const noexcept = 0;
    virtual void updateSpecification(const TextureSpecification &specification) = 0;
    virtual void bind(uint16_t slot) const noexcept = 0;
    virtual uint32_t getPointer() const noexcept = 0;

};

class Texture2DFactory
{
public:
    static Texture2D *create(const TextureSpecification &specification, void *data, size_t dataSize);
    static Texture2D *create(const TextureSpecification &specification);

};

}
#endif //VANADIUM_TEXTURE2D_H
