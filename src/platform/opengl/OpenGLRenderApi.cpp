#include "OpenGLRenderApi.h"
#include "OpenGLIncludes.h"
#include "OpenGLCall.h"
#include "../../core/Log.h"

namespace Vanadium
{

void OpenGLRenderApi::clear() const noexcept
{
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGLRenderApi::clear(const glm::vec4 &color) const noexcept
{
    glCall(glClearColor(color.r, color.g, color.b, color.a));
}

void OpenGLRenderApi::setViewport(const glm::ivec2 &position, const glm::ivec2 &geometry) const noexcept
{
    VAN_ENGINE_TRACE("Resizing viewport to ({}, {}) and moving it to ({}, {})",
                     geometry.x, geometry.y, position.x, position.y);
    glCall(glViewport(position.x, position.y, geometry.x, geometry.y));
}

void OpenGLRenderApi::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const noexcept
{
    VAN_ENGINE_TRACE("Resizing viewport to ({}, {}) and moving it to ({}, {})",
                     width, height, x, y);
    glCall(glViewport(x, y, width, height));
}

}