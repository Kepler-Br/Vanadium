#ifndef VANADIUM_OPENGLRENDERAPI_H
#define VANADIUM_OPENGLRENDERAPI_H

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

#include "../../render/RenderApi.h"
#include "OpenGLBuffer.h"

namespace Vanadium
{

class OpenGLRenderApi: public RenderApi
{
public:
    void clear() const noexcept override;
    void clear(const glm::vec4 &color) const noexcept override;
    void setViewport(const glm::ivec2 &position, const glm::ivec2 &geometry) const noexcept override;
    void setViewport(VNsize x, VNsize y, VNsize width, VNsize height) const noexcept override;
    void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) const noexcept override;
};

}

#endif //VANADIUM_OPENGLRENDERAPI_H
