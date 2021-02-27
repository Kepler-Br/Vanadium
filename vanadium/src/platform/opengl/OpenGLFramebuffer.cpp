#include "OpenGLFramebuffer.h"

#include <utility>
#include "../../core/Log.h"
#include "../../core/Assert.h"
#include "OpenGLCall.h"

namespace Vanadium
{


GLenum OpenGLFramebuffer::textureTarget(bool multisampled)
{
    return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

void OpenGLFramebuffer::createTextures(bool multisampled, uint32_t *outID, uint32_t count)
{
#ifdef VANADIUM_OLD_CORE_OPENGL
    glGenTextures(count, outID);
#else
    glCreateTextures(OpenGLFramebuffer::textureTarget(multisampled), count, outID);
#endif
}

void OpenGLFramebuffer::bindTexture(bool multisampled, uint32_t id)
{
    glBindTexture(textureTarget(multisampled), id);
}

void OpenGLFramebuffer::attachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height,
                                           int index)
{
    bool multisampled = samples > 1;
    if (multisampled)
    {
        // Might not be supported by older OpenGL versions.
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    // Todo: Check color attachment bounds.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multisampled), id, 0);
}

void
OpenGLFramebuffer::attachDepthTexture(uint32_t id, GLsizei samples, GLenum format, GLenum attachmentType, GLsizei width,
                                      GLsizei height)
{
    bool multisampled = samples > 1;
    if (multisampled)
    {
        // Might not be supported by older OpenGL versions.
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
    }
    else
    {
        // Might not be supported by older OpenGL versions.
#ifdef VANADIUM_OLD_CORE_OPENGL
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8,
                        width, height,
                        0, GL_DEPTH24_STENCIL8, GL_UNSIGNED_INT_24_8, nullptr));
#else
        glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
#endif
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    // Might not be supported by older OpenGL versions.
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multisampled), id, 0);
}

bool OpenGLFramebuffer::isDepthFormat(Framebuffer::TextureFormat format)
{
    if (format == Framebuffer::TextureFormat::DepthStencil)
        return true;
    return false;
}

// Todo: split this into smaller functions.
void OpenGLFramebuffer::create()
{
    glGenFramebuffers(1, &this->pointer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->pointer);

    bool multisample = this->specification.samples > 1;

    // Attachments
    if (!this->colorAttachmentSpecifications.empty())
    {
        this->colorAttachments.resize(this->colorAttachmentSpecifications.size());
        OpenGLFramebuffer::createTextures(multisample, this->colorAttachments.data(), this->colorAttachments.size());

        for (size_t i = 0; i < this->colorAttachments.size(); i++)
        {
            OpenGLFramebuffer::bindTexture(multisample, this->colorAttachments[i]);
            switch (this->colorAttachmentSpecifications[i].textureFormat)
            {
                case Framebuffer::TextureFormat::RGBA8:
                    OpenGLFramebuffer::attachColorTexture(this->colorAttachments[i], this->specification.samples, GL_RGBA8, this->specification.width, this->specification.height, i);
                    break;
                default:
                    VAN_ENGINE_ASSERT(false, "OpenGLFramebuffer::create Framebuffer::TextureFormat is not RGBA8.");
                    break;
            }
        }
    }

    if (this->depthAttachmentSpecification.textureFormat != Framebuffer::TextureFormat::None)
    {
        OpenGLFramebuffer::createTextures(multisample, &this->depthAttachment, 1);
        OpenGLFramebuffer::bindTexture(multisample, this->depthAttachment);
        switch (this->depthAttachmentSpecification.textureFormat)
        {
            case Framebuffer::TextureFormat::DepthStencil:
                OpenGLFramebuffer::attachDepthTexture(this->depthAttachment, this->specification.samples,
                                                      GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
                                                      this->specification.width, this->specification.height);
                break;
            default:
                VAN_ENGINE_ASSERT(false, "OpenGLFramebuffer::create Framebuffer::TextureFormat is not DepthStencil.");
                break;
        }
    }

    if (!this->colorAttachments.empty())
    {
        constexpr VNsize maxColorAttachments = 4;
        if (this->colorAttachments.size() > maxColorAttachments)
            VAN_ENGINE_ASSERT((this->colorAttachments.size() <= maxColorAttachments),
                              "Too much texture attachments: {} > {}.",
                              this->colorAttachments.size(), maxColorAttachments);
        GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers(this->colorAttachments.size() > maxColorAttachments ? maxColorAttachments : this->colorAttachments.size(), buffers);
    }
    else
    {
        // Only depth-pass
        glDrawBuffer(GL_NONE);
    }

    VAN_ENGINE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE),
                      "Framebuffer is incomplete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::destroy()
{
    glDeleteFramebuffers(1, &this->pointer);
    glDeleteTextures(this->colorAttachments.size(), this->colorAttachments.data());
    glDeleteTextures(1, &this->depthAttachment);

    this->colorAttachments.clear();
    this->depthAttachment = 0;
}

OpenGLFramebuffer::OpenGLFramebuffer(Framebuffer::Specification specification):
    specification(std::move(specification))
{
    VAN_ENGINE_TRACE("Creating framebuffer.");
    for (auto spec : this->specification.attachments.attachments)
    {
        if (!OpenGLFramebuffer::isDepthFormat(spec.textureFormat))
            this->colorAttachmentSpecifications.emplace_back(spec);
        else
            this->depthAttachmentSpecification = spec;
    }
    this->create();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    VAN_ENGINE_TRACE("Destroying framebuffer.");
    this->destroy();
}

void OpenGLFramebuffer::resize(VNsize width, VNsize height) noexcept
{
    VAN_ENGINE_TRACE("Resizing framebuffer.");
    this->specification.width = width;
    this->specification.height = height;
    this->destroy();
    this->create();
}

void OpenGLFramebuffer::bind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->pointer);
    // Why?
    glViewport(0, 0, this->specification.width, this->specification.height);
}

void OpenGLFramebuffer::unbind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void *OpenGLFramebuffer::getRaw() const noexcept
{
    return (void *)&this->pointer;
}

}
