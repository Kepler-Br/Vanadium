#ifndef VANADIUM_TEXTURE_H
#define VANADIUM_TEXTURE_H

#include <unordered_map>
#include <vector>

#include <glm/vec2.hpp>

#include "../core/Types.h"

namespace Vanadium
{

class Texture
{
public:
    enum class ColorFormat
    {
        RGB = 0,
        RGBA,
    };

    enum class Filtering
    {
        Linear = 0,
        Nearest,
    };

    enum class Wrapping
    {
        Repeat = 0,
        Clamp,
        Mirror,
    };

    struct Specification
    {
        VNsize width, height;
        Texture::ColorFormat colorFormat = Texture::ColorFormat::RGB;
        Texture::ColorFormat internalFormat = Texture::ColorFormat::RGB;
        Texture::Filtering magnificationFilter = Texture::Filtering::Nearest;
        Texture::Filtering minificationFilter = Texture::Filtering::Nearest;
        Texture::Wrapping wrapping = Texture::Wrapping::Repeat;
    };

public:
    virtual VNsize getWidth() const noexcept = 0;
    virtual VNsize getHeight() const noexcept = 0;
    virtual glm::ivec2 getGeometry() const noexcept = 0;
    virtual void setData(void* data, VNsize size) noexcept = 0;
    virtual void setData(const std::vector<int8_t> &data) noexcept = 0;
    virtual void setWrapping(Texture::Wrapping wrapping) noexcept = 0;
    virtual void setMagnificationFiltering(Texture::Filtering filtering) noexcept = 0;
    virtual void setMinificationFiltering(Texture::Filtering filtering) noexcept = 0;
    virtual const Texture::Specification &getSpecification() const noexcept = 0;
    virtual void bind(VNuint slot) const noexcept = 0;
    virtual void *getRaw() const noexcept = 0;

};

class TextureFactory
{
    using TextureContainer = std::unordered_map<std::string, WeakRef<Texture>>;

    static TextureContainer textureContainer;
    static Ref<Texture> get(const std::string &path);
    static void set(const std::string &path, const Ref<Texture> &texture);

public:
    static Ref<Texture> create(const std::string &path, Texture::Specification specification = Texture::Specification());
    static Ref<Texture> create(void *data, const Texture::Specification &specification = Texture::Specification());

};

}
#endif //VANADIUM_TEXTURE_H
