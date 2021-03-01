#include "Texture.h"
#include "../core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../vfs/Vfs.h"
#include <sstream>

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLTexture.h"
    using TextureImpl = Vanadium::OpenGLTexture;
#else
    #error "Not a supported API."
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


Ref<Texture> TextureFactory::create(const std::string &path, Texture::Specification specification)
{
    int width, height, channels;
    stbi_uc* data;
    Ref<Texture> texture;

    VAN_ENGINE_TRACE("Loading texture from VFS: \"{}\".", path);
    if (!Vfs::exists(path))
    {
        VAN_ENGINE_ERROR("Unable to load texture - does not exist. Path: {}.", path);
        return nullptr;
    }
    std::stringstream dataFromVfs = Vfs::readWhole(path);
    data = stbi_load_from_memory((const stbi_uc *)dataFromVfs.rdbuf(), dataFromVfs.tellp(), &width, &height, &channels, 0);
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
    texture = TextureFactory::create((void *)data, specification);
    stbi_image_free(data);
    return texture;
}

Ref<Texture> TextureFactory::create(void *data, const Texture::Specification &specification)
{
    VAN_ENGINE_TRACE("Creating Texture.");
    return MakeRef<TextureImpl>(data, specification);
}

}