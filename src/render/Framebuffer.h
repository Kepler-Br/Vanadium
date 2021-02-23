#ifndef VANADIUM_FRAMEBUFFER_H
#define VANADIUM_FRAMEBUFFER_H

#include <glm/vec2.hpp>
#warning "Implement Framebuffer factory."

namespace Vanadium
{

class Framebuffer
{
public:
    virtual void resize(uint32_t width, uint32_t height) noexcept = 0;
    virtual void resize(const glm::ivec2 &geometry) noexcept = 0;
    virtual void bind() noexcept = 0;
    virtual void unbind() noexcept = 0;
    virtual void destroy() = 0;

};

class FramebufferFactory
{
public:
    static Framebuffer *create(uint32_t width, uint32_t height);

};

}
#endif //VANADIUM_FRAMEBUFFER_H
