#ifndef VANADIUM_OPENGLPOSTPROCESSING_H
#define VANADIUM_OPENGLPOSTPROCESSING_H

#include "../../render/Postprocessing.h"

namespace Vanadium
{

class Shader;
class Framebuffer;
class VertexArray;

class OpenGLPostprocessing : public Postprocessing
{
private:
    Ref<Shader> shader;
    Ref<Framebuffer> framebuffer;
    Ref<VertexArray> vao;

public:
    OpenGLPostprocessing() = default;

    explicit OpenGLPostprocessing(Ref<Shader> shader);

    ~OpenGLPostprocessing() = default;
    void bind() noexcept;
    void unbind() noexcept;
    void draw() noexcept;
    void setShader(Ref<Shader> shader) noexcept;
    Ref<Shader> getShader() noexcept;
    Ref<Framebuffer> getFramebuffer() noexcept;

};

}
#endif //VANADIUM_OPENGLPOSTPROCESSING_H
