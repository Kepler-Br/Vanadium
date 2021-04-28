#include "platform/opengl/OpenGLPostprocessing.h"

#include <glm/gtc/type_ptr.hpp>

#include "platform/opengl/OpenGLFramebuffer.h"
#include "render/Framebuffer.h"
#include "render/IndexBuffer.h"
#include "render/Shader.h"
#include "render/VertexArray.h"
#include "scene/Mesh.h"

namespace Vanadium {

OpenGLPostprocessing::OpenGLPostprocessing(const Ref<Shader> &shader,
                                           VNuint width, VNuint height)
    : shader(shader) {
  Framebuffer::Specification specs = {width, height,
                                      Framebuffer::AttachmentSpecification({
                                          Framebuffer::TextureFormat::Depth,
                                          Framebuffer::TextureFormat::RGBA8,
                                      }),
                                      1, Texture::Filtering::Linear};
  this->framebuffer = FramebufferFactory::create(specs);
  this->screenPlane = MeshFactory::unitPlane(2.0f);
}

OpenGLPostprocessing::OpenGLPostprocessing(
    const Ref<Shader> &shader, const Framebuffer::Specification &specification)
    : shader(shader) {
  this->framebuffer = FramebufferFactory::create(specification);
  this->screenPlane = MeshFactory::unitPlane(2.0f);
}

void OpenGLPostprocessing::bind() noexcept {
  glGetIntegerv(GL_VIEWPORT, glm::value_ptr(this->viewportSize));
  this->framebuffer->bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLPostprocessing::unbind() noexcept {
  this->framebuffer->unbind();
  glViewport(this->viewportSize.x, this->viewportSize.y, this->viewportSize.z,
             this->viewportSize.w);
}

void OpenGLPostprocessing::draw() noexcept {
  this->screenPlane->bind();
  VNuint framebufferTexture =
      *(VNuint *)this->framebuffer->getColorAttachment(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, framebufferTexture);
  glDrawElements(
      GL_TRIANGLES,
      this->screenPlane->getVertexArray()->getIndexBuffer()->getCount(),
      GL_UNSIGNED_INT, nullptr);
  this->screenPlane->unbind();
}

void OpenGLPostprocessing::setShader(const Ref<Shader> &shader) noexcept {
  this->shader = shader;
}

void OpenGLPostprocessing::bindShader() noexcept { this->shader->bind(); }

void OpenGLPostprocessing::unbindShader() noexcept { this->shader->unbind(); }

Ref<Shader> OpenGLPostprocessing::getShader() noexcept { return this->shader; }

Ref<Framebuffer> OpenGLPostprocessing::getFramebuffer() noexcept {
  return this->framebuffer;
}

}  // namespace Vanadium