#include "platform/opengl/OpenGLRenderApi.h"

#include "core/Log.h"
#include "platform/opengl/OpenGLCall.h"
#include "platform/opengl/OpenGLIncludes.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "scene/Mesh.h"

namespace Vanadium {

void OpenGLRenderApi::clear() const noexcept {
  glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGLRenderApi::clear(const glm::vec4 &color) const noexcept {
  glCall(glClearColor(color.r, color.g, color.b, color.a));
}

void OpenGLRenderApi::setViewport(const glm::ivec2 &position,
                                  const glm::ivec2 &geometry) const noexcept {
  //    VAN_ENGINE_TRACE("Resizing viewport to ({}, {}) and moving it to ({},
  //    {})",
  //                     geometry.x, geometry.y, position.x, position.y);
  glCall(glViewport(position.x, position.y, geometry.x, geometry.y));
}

void OpenGLRenderApi::setViewport(VNint x, VNint y, VNsize width,
                                  VNsize height) const noexcept {
  //    VAN_ENGINE_TRACE("Resizing viewport to ({}, {}) and moving it to ({},
  //    {})",
  //                     width, height, x, y);
  glCall(glViewport(x, y, width, height));
}

void OpenGLRenderApi::drawIndexed(const Ref<VertexArray> &vertexArray,
                                  VNsize indexCount) const noexcept {
  VNsize count =
      indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRenderApi::drawMesh(Ref<Mesh> mesh) const noexcept {
  if (mesh == nullptr || !(*mesh)) {
    return;
  }
  mesh->bind();
  VNsize indexCount = mesh->getVertexArray()->getIndexBuffer()->getCount();
  if (mesh->getPrimitiveType() == Mesh::PrimitiveType::Lines) {
    glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, nullptr);
  } else if (mesh->getPrimitiveType() == Mesh::PrimitiveType::Triangles) {
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
  } else {
    VAN_ENGINE_ERROR("OpenGLRenderApi::drawMesh: Unknown mesh primitive type.");
  }
  mesh->unbind();
}

}  // namespace Vanadium