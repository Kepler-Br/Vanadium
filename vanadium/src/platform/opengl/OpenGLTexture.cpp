#include "OpenGLTexture.h"

#include "../../core/Assert.h"
#include "../../core/Log.h"
#include "OpenGLCall.h"

namespace Vanadium {

GLenum OpenGLTexture::wrapToOpenGLWrap(Texture::Wrapping wrapping) {
  switch (wrapping) {
    case Texture::Wrapping::Repeat:
      return GL_REPEAT;
    case Texture::Wrapping::Clamp:
      return GL_CLAMP_TO_EDGE;
    case Texture::Wrapping::Mirror:
      return GL_MIRRORED_REPEAT;
  }
  VAN_ENGINE_ASSERT(
      false,
      "OpenGLTexture::wrapToOpenGLWrap: invalid texture wrapping format.");
  return GL_REPEAT;
}

GLenum OpenGLTexture::filteringToOpenGLFiltering(Texture::Filtering filtering) {
  switch (filtering) {
    case Texture::Filtering::Nearest:
      return GL_NEAREST;
    case Texture::Filtering::Linear:
      return GL_LINEAR;
  }
  VAN_ENGINE_ASSERT(false,
                    "OpenGLTexture::filteringToOpenGLFiltering: invalid "
                    "texture filtering format.");
  return GL_NEAREST;
}

GLenum OpenGLTexture::colorFormatToOpenGLTextureInternalColorFormat(
    Texture::ColorFormat colorFormat) {
  switch (colorFormat) {
    case Texture::ColorFormat::RGB:
      return GL_RGB8;
    case Texture::ColorFormat::RGBA:
      return GL_RGBA8;
  }
  VAN_ENGINE_ASSERT(false,
                    "OpenGLTexture::colorFormatToOpenGLTextureColorFormat: "
                    "invalid internal texture color format.");
  return GL_RGB8;
}

GLenum OpenGLTexture::colorFormatToOpenGLTextureColorFormat(
    Texture::ColorFormat colorFormat) {
  switch (colorFormat) {
    case Texture::ColorFormat::RGB:
      return GL_RGB;
    case Texture::ColorFormat::RGBA:
      return GL_RGBA;
  }
  VAN_ENGINE_ASSERT(false,
                    "OpenGLTexture::colorFormatToOpenGLTextureColorFormat: "
                    "invalid texture color format.");
  return GL_RGB;
}

void OpenGLTexture::init(void *data,
                         const Texture::Specification &specification) {
  constexpr GLint levelOfDetail = 0;
  constexpr GLint border = 0;
  this->specification = specification;
  this->size = specification.width * specification.height;
  GLenum internalTextureColorFormat =
      OpenGLTexture::colorFormatToOpenGLTextureInternalColorFormat(
          specification.internalFormat);
  GLenum textureColorFormat =
      OpenGLTexture::colorFormatToOpenGLTextureColorFormat(
          specification.colorFormat);

  glGenTextures(1, &this->pointer);
  glBindTexture(GL_TEXTURE_2D, this->pointer);
  glCall(glTexImage2D(GL_TEXTURE_2D, levelOfDetail, internalTextureColorFormat,
                      (GLsizei)specification.width,
                      (GLsizei)specification.height, border, textureColorFormat,
                      GL_UNSIGNED_BYTE, data));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  OpenGLTexture::filteringToOpenGLFiltering(
                      specification.magnificationFilter));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  OpenGLTexture::filteringToOpenGLFiltering(
                      specification.minificationFilter));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  OpenGLTexture::wrapToOpenGLWrap(specification.wrapping));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                  OpenGLTexture::wrapToOpenGLWrap(specification.wrapping));
}

OpenGLTexture::OpenGLTexture(void *data,
                             const Texture::Specification &specification) {
  //    VAN_ENGINE_TRACE("Creating texture with dimensions: ({}, {}).",
  //    specification.width, specification.height);
  this->init(data, specification);
}

OpenGLTexture::~OpenGLTexture() {
  //    VAN_ENGINE_TRACE("Destroying texture.");
  glDeleteTextures(1, &this->pointer);
}

VNsize OpenGLTexture::getWidth() const noexcept {
  return this->specification.width;
}

VNsize OpenGLTexture::getHeight() const noexcept {
  return this->specification.height;
}

glm::ivec2 OpenGLTexture::getGeometry() const noexcept {
  return {this->specification.width, this->specification.height};
}

void OpenGLTexture::setData(void *data, VNsize size) noexcept {
  GLenum textureColorFormat =
      OpenGLTexture::colorFormatToOpenGLTextureColorFormat(
          specification.colorFormat);

  //    VAN_ENGINE_TRACE("Updating texture data.");
  if (size > this->size) {
    VAN_ENGINE_ERROR(
        "Cannot update texture data with different pixel count. Current: {}; "
        "new: {}).",
        this->size, size);
    return;
  }
  glCall(glTexSubImage2D(this->pointer, 0, 0, 0,
                         (GLsizei)this->specification.width,
                         (GLsizei)this->specification.height,
                         textureColorFormat, GL_UNSIGNED_BYTE, data));
}

void OpenGLTexture::setData(const std::vector<int8_t> &data) noexcept {
  this->setData((void *)&data[0], data.size());
}

const Texture::Specification &OpenGLTexture::getSpecification() const noexcept {
  return this->specification;
}

// Todo: add total possible texture count to bind.
void OpenGLTexture::bind(VNuint slot) const noexcept {
  glCall(glActiveTexture(GL_TEXTURE0 + slot));
  glBindTexture(GL_TEXTURE_2D, this->pointer);
}

void *OpenGLTexture::getRaw() const noexcept { return (void *)&this->pointer; }

bool OpenGLTexture::operator!() const noexcept { return (this->pointer == 0); }

}  // namespace Vanadium