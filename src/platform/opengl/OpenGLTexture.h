#ifndef VANADIUM_OPENGLTEXTURE_H
#define VANADIUM_OPENGLTEXTURE_H

#include <vector>

#include "../../core/Types.h"
#include "../../render/Texture.h"
#include "OpenGLIncludes.h"

namespace Vanadium {

class OpenGLTexture : public Texture {
 private:
  Texture::Specification specification;
  GLuint pointer = 0;
  VNsize size = 0;

  void init(void *data, const Texture::Specification &specification);

  static GLenum wrapToOpenGLWrap(Texture::Wrapping wrapping);
  static GLenum filteringToOpenGLFiltering(Texture::Filtering filtering);
  static GLenum colorFormatToOpenGLTextureInternalColorFormat(
      Texture::ColorFormat colorFormat);
  static GLenum colorFormatToOpenGLTextureColorFormat(
      Texture::ColorFormat colorFormat);

 public:
  OpenGLTexture(void *data, const Texture::Specification &specification);
  ~OpenGLTexture();

  [[nodiscard]] VNsize getWidth() const noexcept override;
  [[nodiscard]] VNsize getHeight() const noexcept override;
  [[nodiscard]] glm::ivec2 getGeometry() const noexcept override;
  void setData(void *data, VNsize size) noexcept override;
  void setData(const std::vector<int8_t> &data) noexcept override;
  void setWrapping(Texture::Wrapping wrapping) noexcept override {
    this->specification.wrapping = wrapping;
    glGenTextures(1, &this->pointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    OpenGLTexture::wrapToOpenGLWrap(specification.wrapping));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    OpenGLTexture::wrapToOpenGLWrap(specification.wrapping));
  }
  void setMagnificationFiltering(
      Texture::Filtering filtering) noexcept override {
    this->specification.magnificationFilter = filtering;
    glGenTextures(1, &this->pointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    OpenGLTexture::filteringToOpenGLFiltering(
                        specification.magnificationFilter));
  }
  void setMinificationFiltering(
      Texture::Filtering filtering) noexcept override {
    this->specification.minificationFilter = filtering;
    glGenTextures(1, &this->pointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    OpenGLTexture::filteringToOpenGLFiltering(
                        specification.minificationFilter));
  }
  [[nodiscard]] const Texture::Specification &getSpecification()
      const noexcept override;
  void bind(VNuint slot) const noexcept override;
  [[nodiscard]] void *getRaw() const noexcept override;
  bool operator!() const noexcept override;
};

}  // namespace Vanadium

#endif  // VANADIUM_OPENGLTEXTURE_H
