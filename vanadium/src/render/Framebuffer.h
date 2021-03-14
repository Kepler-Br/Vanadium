#ifndef VANADIUM_FRAMEBUFFER_H
#define VANADIUM_FRAMEBUFFER_H

#include <vector>

#include <glm/vec2.hpp>

#include "../core/Types.h"
#include "Texture.h"

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
        Depth = (int)DepthStencil
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
        AttachmentSpecification(const std::initializer_list<Framebuffer::TextureSpecification> &list):
            attachments(list)
        {}
        std::vector<Framebuffer::TextureSpecification> attachments;
    };

    struct Specification
    {
        VNsize width = 0, height = 0;
        Framebuffer::AttachmentSpecification attachments;
        VNsize samples = 1;
        Texture::Filtering filtering = Texture::Filtering::Linear;
        // Why?
//        bool swapchain = false;
    };

public:
    virtual void resize(VNsize width, VNsize height) noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    [[nodiscard]]
    virtual void *getRaw() const noexcept = 0;
    [[nodiscard]]
    virtual VNuint getWidth() const noexcept = 0;
    [[nodiscard]]
    virtual VNuint getHeight() const noexcept = 0;
    [[nodiscard]]
    virtual glm::vec2 getGeometry() const noexcept = 0;
    virtual bool operator!() const noexcept = 0;
    [[nodiscard]]
    virtual void *getColorAttachment(VNsize index) const noexcept = 0;
    [[nodiscard]]
    virtual void *getDepthAttachment() const noexcept = 0;

};

class FramebufferFactory
{
public:
    static Ref<Framebuffer> create(const Framebuffer::Specification &specification);
};

}
#endif //VANADIUM_FRAMEBUFFER_H
