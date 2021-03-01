#ifndef VANADIUM_RENDERAPI_H
#define VANADIUM_RENDERAPI_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "../core/Types.h"

namespace Vanadium
{
class VertexArray;

class RenderApi
{
private:
    static RenderApi *renderApi;

public:
    enum class Api
    {
        OpenGL = 0,
        OpenGLES,
        WebGL,
        Vulkan,
        Metal,
        DirectX,
        DirectX12,
    };

    virtual void clear() const noexcept = 0;
    virtual void clear(const glm::vec4 &color) const noexcept = 0;
    virtual void setViewport(const glm::ivec2 &position, const glm::ivec2 &geometry) const noexcept = 0;
    virtual void setViewport(VNsize x, VNsize y, VNsize width, VNsize height) const noexcept = 0;
    virtual void drawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount) const noexcept = 0;

    static RenderApi *instance();
    static Api getApi();
    static std::string apiToString(Api api);
};

}
#endif //VANADIUM_RENDERAPI_H
