#ifndef VANADIUM_OPENGLTEXTURE2D_H
#define VANADIUM_OPENGLTEXTURE2D_H

#include "../../render/Texture2D.h"
#include "OpenGLIncludes.h"

namespace Van
{

class OpenGLTexture2D : public Texture2D
{
private:
    TextureSpecification specification;
    uint32_t texturePointer = 0;

public:
    uint32_t getWidth() const noexcept override;
    uint32_t getHeight() const noexcept override;
    glm::ivec2 getGeometry() const noexcept override;
    void destroy() noexcept override;
    void resize(const glm::ivec2 &newGeometry) override;
    void resize(uint32_t newWidth, uint32_t newHeight) override;
    void setData(void* data, uint32_t size) noexcept override;
    TextureSpecification getSpecification() const noexcept override;
    void updateSpecification(const TextureSpecification &specification) override;
    void bind(uint16_t slot) const noexcept override;
    uint32_t getPointer() const noexcept override;

};

}

#endif //VANADIUM_OPENGLTEXTURE2D_H
