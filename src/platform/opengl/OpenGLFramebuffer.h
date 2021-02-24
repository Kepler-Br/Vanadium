#ifndef VANADIUM_OPENGLFRAMEBUFFER_H
#define VANADIUM_OPENGLFRAMEBUFFER_H

#include <vector>

#include "../../render/Framebuffer.h"

namespace Vanadium
{

class OpenGLFramebuffer : public Framebuffer
{
private:
    Framebuffer::Specification specification;
    GLuint pointer;
    GLuint depthAttachment;
    std::vector<GLuint> colorAttachments;
    std::vector<Framebuffer::TextureSpecification> colorAttachmentSpecifications;
    Framebuffer::TextureSpecification depthAttachmentSpecification = Framebuffer::TextureFormat::None;

    void create();
    void destroy();

    static GLenum textureTarget(bool multisampled);
    static void createTextures(bool multisampled, uint32_t* outID, uint32_t count);
    static void bindTexture(bool multisampled, uint32_t id);
    static void attachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, int index);
    static void attachDepthTexture(uint32_t id, GLsizei samples, GLenum format, GLenum attachmentType, GLsizei width, GLsizei height);
    static bool isDepthFormat(Framebuffer::TextureFormat format);

public:
    explicit OpenGLFramebuffer(Framebuffer::Specification specification);
    ~OpenGLFramebuffer();
    void resize(VNsize width, VNsize height) noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    void *getRaw() const noexcept override;

};

}


#endif //VANADIUM_OPENGLFRAMEBUFFER_H
