#include "Texture.h"

#include "../core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../vfs/Vfs.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "../platform/opengl/OpenGLTexture.h"
using TextureImpl = Vanadium::OpenGLTexture;
#else
#error "Not a supported API."
#endif

namespace Vanadium {

Ref<Texture> TextureFactory::create(const std::string &path,
                                    Texture::Specification specification) {
  int width, height, channels;
  stbi_uc *data;
  Ref<Texture> texture;

  VAN_ENGINE_TRACE("Loading texture from VFS: \"{}\".", path);
  if (!Vfs::exists(path)) {
    VAN_ENGINE_ERROR("Unable to load texture - does not exist. Path: {}.",
                     path);
    return nullptr;
  }

  std::vector<char> dataFromVfs = Vfs::readWhole(path);
  Vfs::ErrorCode err = Vfs::getErrorCode();
  if (err != Vfs::ErrorCode::OK) {
    VAN_ENGINE_ERROR("Unable to load texture: {}. Vfs error: {}", path,
                     Vfs::errorCodeToString(err));
    return nullptr;
  }
  data = stbi_load_from_memory((const stbi_uc *)(&dataFromVfs[0]),
                               (int)dataFromVfs.size(), &width, &height,
                               &channels, 0);
  if (!data) {
    VAN_ENGINE_ERROR("Unable to load texture: {}.", path);
    return nullptr;
  }
  if (channels == 4) {
    specification.internalFormat = Texture::ColorFormat::RGBA;
    specification.colorFormat = Texture::ColorFormat::RGBA;
  } else if (channels == 3) {
    specification.internalFormat = Texture::ColorFormat::RGB;
    specification.colorFormat = Texture::ColorFormat::RGB;
  } else {
    VAN_ENGINE_ERROR("Unsupported texture channel count: {}.", channels);
    stbi_image_free(data);
    return nullptr;
  }
  specification.width = (VNsize)width;
  specification.height = (VNsize)height;
  texture = TextureFactory::create((void *)data, specification);
  stbi_image_free(data);
  return texture;
}

Ref<Texture> TextureFactory::create(
    void *data, const Texture::Specification &specification) {
  VAN_ENGINE_TRACE("Uploading data to texture.");
  return MakeRef<TextureImpl>(data, specification);
}

}  // namespace Vanadium