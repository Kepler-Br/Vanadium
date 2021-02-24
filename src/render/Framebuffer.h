#ifndef VANADIUM_FRAMEBUFFER_H
#define VANADIUM_FRAMEBUFFER_H

#include <vector>

#include <glm/vec2.hpp>

#include "../core/Types.h"

namespace Vanadium
{

class Framebuffer
{
public:
    enum class TextureFormat
    {
        None = 0,
        RGBA8,
        DepthStencil,
        Depth = DepthStencil
    };

    struct TextureSpecification
    {
        TextureSpecification() = default;
        TextureSpecification(Framebuffer::TextureFormat format)
            : textureFormat(format) {}
        Framebuffer::TextureFormat textureFormat = Framebuffer::TextureFormat::None;
    };

    struct AttachmentSpecification
    {
        AttachmentSpecification(std::initializer_list<Framebuffer::TextureSpecification> &list):
            attachments(list)
        {}
        std::vector<Framebuffer::TextureSpecification> attachments;
    };

    struct Specification
    {
        VNsize width, height;
        Framebuffer::AttachmentSpecification attachments;
        VNsize samples = 1;

        // Why?
//        bool swapchain = false;
    };

public:
    virtual void resize(VNsize width, VNsize height) noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual void *getRaw() const noexcept = 0;

};

class FramebufferFactory
{
public:
    static Ref<Framebuffer> create(const Framebuffer::Specification &specification);
};

}
#endif //VANADIUM_FRAMEBUFFER_H
