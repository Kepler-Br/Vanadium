#ifndef VANADIUM_OPENGLFRAMEBUFFER_H
#define VANADIUM_OPENGLFRAMEBUFFER_H

#include <vector>

#include "../../render/Framebuffer.h"
#include "../../render/Texture.h"

namespace Vanadium
{

class OpenGLFramebuffer : public Framebuffer
{
private:
    Framebuffer::Specification specification;
    GLuint pointer = 0;
    GLuint depthAttachment;
    std::vector<GLuint> colorAttachments;
    std::vector<Framebuffer::TextureSpecification> colorAttachmentSpecifications;
    Framebuffer::TextureSpecification depthAttachmentSpecification =
            Framebuffer::TextureSpecification{Framebuffer::TextureFormat::None};

    void create();
    void destroy();

    static GLenum textureTarget(bool multisampled);
    static void createTextures(bool multisampled, GLuint *outID, VNsize count);
    static void bindTexture(bool multisampled, VNsize id);
    void attachColorTexture(VNsize id, int samples, GLenum format, VNsize width, VNsize height, int index);
    void attachDepthTexture(uint32_t id, GLsizei samples, GLenum format, GLenum attachmentType, GLsizei width, GLsizei height);
    static bool isDepthFormat(Framebuffer::TextureFormat format);

public:
    explicit OpenGLFramebuffer(Framebuffer::Specification specification);
    ~OpenGLFramebuffer();
    void resize(VNsize width, VNsize height) noexcept override;
    void bind() const noexcept override;
    void unbind() const noexcept override;
    [[nodiscard]]
    void *getRaw() const noexcept override;
    [[nodiscard]]
    VNuint getWidth() const noexcept override;
    [[nodiscard]]
    VNuint getHeight() const noexcept override;
    glm::vec2 getGeometry() const noexcept override;
    bool operator!() const noexcept override;
    GLuint getColorAttachment(VNsize index) const noexcept;

};

}


#endif //VANADIUM_OPENGLFRAMEBUFFER_H
