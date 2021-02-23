#include "OpenGLTexture2D.h"

namespace Vanadium
{

uint32_t OpenGLTexture2D::getWidth() const noexcept
{
    return this->specification.width;
}

uint32_t OpenGLTexture2D::getHeight() const noexcept
{
    return this->specification.height;
}

glm::ivec2 OpenGLTexture2D::getGeometry() const noexcept
{
    return {this->specification.width, this->specification.height};
}

void OpenGLTexture2D::destroy() noexcept
{

}

void OpenGLTexture2D::resize(const glm::ivec2 &newGeometry)
{

}

void OpenGLTexture2D::resize(uint32_t newWidth, uint32_t newHeight)
{

}

void OpenGLTexture2D::setData(void *data, uint32_t size) noexcept
{

}

TextureSpecification OpenGLTexture2D::getSpecification() const noexcept
{
    return this->specification;
}

void OpenGLTexture2D::updateSpecification(const Vanadium::TextureSpecification &specification)
{
    this->specification = specification;
}

void OpenGLTexture2D::bind(uint16_t slot) const noexcept
{

}

uint32_t OpenGLTexture2D::getPointer() const noexcept
{
    return this->texturePointer;
}

}