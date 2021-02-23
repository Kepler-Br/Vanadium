#ifndef VANADIUM_RENDERAPI_H
#define VANADIUM_RENDERAPI_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Vanadium
{

class RenderApi
{
private:
    static RenderApi *renderApi;

public:
    enum class Api
    {
        OpenGL = 0,
        OpenGLES,
        DirectX,
        DirectX12,
        Vulkan,
    };

    virtual void clear() const noexcept = 0;
    virtual void clear(const glm::vec4 &color) const noexcept = 0;
    virtual void setViewport(const glm::ivec2 &position, const glm::ivec2 &geometry) const noexcept = 0;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const noexcept = 0;

    static RenderApi *instance();

    static Api getApi();
};

}
#endif //VANADIUM_RENDERAPI_H
