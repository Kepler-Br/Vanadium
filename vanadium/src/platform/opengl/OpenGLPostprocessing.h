#ifndef VANADIUM_OPENGLPOSTPROCESSING_H
#define VANADIUM_OPENGLPOSTPROCESSING_H

#include "../../render/Postprocessing.h"
#include "../../render/Framebuffer.h"

namespace Vanadium
{

class Mesh;
class Shader;
class Framebuffer;

class OpenGLPostprocessing : public Postprocessing
{
private:
    Ref<Framebuffer> framebuffer;
    Ref<Mesh> screenPlane;
    Ref<Shader> shader;
    glm::ivec4 viewportSize = glm::ivec4(0.0f);

public:
    OpenGLPostprocessing() = default;

    explicit OpenGLPostprocessing(const Ref<Shader> &shader, VNuint width, VNuint height);
    OpenGLPostprocessing(const Ref<Shader> &shader, const Framebuffer::Specification &specification);

    ~OpenGLPostprocessing() = default;
    void bind() noexcept override;
    void unbind() noexcept override;
    void draw() noexcept override;
    void setShader(const Ref<Shader> &shader) noexcept override;
    void bindShader() noexcept override;
    void unbindShader() noexcept override;
    Ref<Shader> getShader() noexcept override;
    Ref<Framebuffer> getFramebuffer() noexcept override;

};

}
#endif //VANADIUM_OPENGLPOSTPROCESSING_H
