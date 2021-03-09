#ifndef VANADIUM_POSTPROCESSING_H
#define VANADIUM_POSTPROCESSING_H

#include "../core/Types.h"

namespace Vanadium
{

class Shader;
class Framebuffer;

class Postprocessing
{
public:
    virtual void bind() noexcept = 0;
    virtual void unbind() noexcept = 0;
    virtual void draw() noexcept = 0;
    virtual void setShader(Ref<Shader> shader) noexcept = 0;
    virtual Ref<Shader> getShader() noexcept = 0;
    virtual Ref<Framebuffer> getFramebuffer() noexcept = 0;

};

class PostprocessingFactory
{
public:
    static Ref<Postprocessing> create();
    static Ref<Postprocessing> create(Ref<Shader> shader);
};

}
#endif //VANADIUM_POSTPROCESSING_H
