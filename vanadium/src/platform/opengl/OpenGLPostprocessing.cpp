#include "OpenGLPostprocessing.h"


namespace Vanadium
{

OpenGLPostprocessing::OpenGLPostprocessing(Ref<Shader> shader) :
        shader(shader)
{

}

void OpenGLPostprocessing::bind() noexcept
{

}

void OpenGLPostprocessing::unbind() noexcept
{

}

void OpenGLPostprocessing::draw() noexcept
{

}

void OpenGLPostprocessing::setShader(Ref<Shader> shader) noexcept
{
    this->shader = shader;
}

Ref<Shader> OpenGLPostprocessing::getShader() noexcept
{
    return this->shader;
}

Ref<Framebuffer> OpenGLPostprocessing::getFramebuffer() noexcept
{
    return this->framebuffer;
}

}