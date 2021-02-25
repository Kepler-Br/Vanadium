#include "Texture.h"
#include "../core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLTexture.h"
#endif

namespace Vanadium
{

using TextureContainer = std::unordered_map<std::string, WeakRef<Texture>>;

TextureContainer TextureFactory::textureContainer;


Ref<Texture> TextureFactory::get(const std::string &path)
{
    auto found = TextureFactory::textureContainer.find(path);

    if (found == TextureFactory::textureContainer.end())
    {
        VAN_ENGINE_TRACE("TextureFactory::get: texture not found in the library: {}.", path);
        return nullptr;
    }
    if (found->second.expired())
    {
        VAN_ENGINE_TRACE("TextureFactory::get: texture pointer has expired: {}.", path);
        TextureFactory::textureContainer.erase(found);
        return nullptr;
    }
    return found->second.lock();
}

void TextureFactory::set(const std::string &path, const Ref<Texture> &texture)
{
    TextureFactory::textureContainer.emplace(path, texture);
}


Ref<Texture> TextureFactory::create(const std::string &path, Texture::Specification specification,
                                    bool forceReload, bool doNotStore)
{
    int width, height, channels;
    stbi_uc* data;
    Ref<Texture> texture;

    if (forceReload)
    {
        VAN_ENGINE_TRACE("Trying to locate texture in library: \"{}\".", path);
        texture = TextureFactory::get(path);
        if (texture)
            return texture;
    }
    VAN_ENGINE_TRACE("Loading texture from disk: \"{}\".", path);
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        VAN_ENGINE_ERROR("Unable to load texture: {}.", path);
        return nullptr;
    }
    if (channels == 4)
    {
        specification.internalFormat = Texture::ColorFormat::RGBA;
        specification.colorFormat = Texture::ColorFormat::RGBA;
    }
    else if (channels == 3)
    {
        specification.internalFormat = Texture::ColorFormat::RGB;
        specification.colorFormat = Texture::ColorFormat::RGB;
    }
    else
    {
        VAN_ENGINE_ERROR("Unsupported texture channel count: {}.", channels);
        stbi_image_free(data);
        return nullptr;
    }
    specification.width = width;
    specification.height = height;
    texture = TextureFactory::create(specification, (void *)data);
    stbi_image_free(data);
    if (!doNotStore && texture)
        TextureFactory::set(path, texture);
    return texture;
}

Ref<Texture> TextureFactory::create(const Texture::Specification &specification,
                                    void *data)
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return MakeRef<OpenGLTexture>(data, specification);
#else
    #error "Unsupported render API."
#endif
}

}