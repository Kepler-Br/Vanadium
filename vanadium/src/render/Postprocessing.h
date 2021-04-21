#ifndef VANADIUM_POSTPROCESSING_H
#define VANADIUM_POSTPROCESSING_H

#include "../core/Types.h"
#include "Framebuffer.h"

namespace Vanadium {

class Shader;

class Postprocessing {
 public:
  virtual void bind() noexcept = 0;
  virtual void unbind() noexcept = 0;
  virtual void draw() noexcept = 0;
  virtual void setShader(const Ref<Shader> &shader) noexcept = 0;
  virtual void bindShader() noexcept = 0;
  virtual void unbindShader() noexcept = 0;
  virtual Ref<Shader> getShader() noexcept = 0;
  virtual Ref<Framebuffer> getFramebuffer() noexcept = 0;
};

class PostprocessingFactory {
 public:
  static Ref<Postprocessing> create(const Ref<Shader> &shader, VNuint width,
                                    VNuint height);
  static Ref<Postprocessing> create(const Ref<Shader> &shader,
                                    const Framebuffer::Specification &specs);
};

}  // namespace Vanadium

#include "Framebuffer.h"
#endif  // VANADIUM_POSTPROCESSING_H
