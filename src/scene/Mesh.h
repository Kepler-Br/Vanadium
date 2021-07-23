#ifndef VANADIUM_MESH_H
#define VANADIUM_MESH_H

#include <bgfx/bgfx.h>

#include "../core/Types.h"

namespace vanadium {

class Mesh {
 public:
  enum class PrimitiveType {
    Lines = 0,
    LineLoop,
    Triangles,
  };

 protected:
  bgfx::IndexBufferHandle _indexBuffer;
  bgfx::VertexBufferHandle _vertexBuffer;

  PrimitiveType _primitiveType;

 public:
  Mesh(bgfx::IndexBufferHandle indexBuffer,
       bgfx::VertexBufferHandle vertexBuffer, PrimitiveType targetPrimitiveType);

  virtual ~Mesh();;

  void bind(uint8_t stream) noexcept;

  [[nodiscard]] const bgfx::IndexBufferHandle &getIndexBuffer() const noexcept;

  [[nodiscard]] const bgfx::VertexBufferHandle &getVertexBuffer()
      const noexcept;

  bool operator!();
};

class MeshFactory {
 public:
  //  static Ref<Mesh> wireframePlane(glm::vec2 bottomLeft, glm::vec2
  //  bottomRight,
  //                                  glm::vec2 topLeft, glm::vec2 topRight);
  //  static Ref<Mesh> unitWireframePlane(float multiplication = 1.0f);
  static Ref<Mesh> plane(glm::vec3 bottomLeft, glm::vec3 bottomRight,
                         glm::vec3 topLeft, glm::vec3 topRight);
  static Ref<Mesh> unitPlane(float multiplication = 1.0f);
  //  static Ref<Mesh> unitCube(float multiplication = 1.0f);
  //  static Ref<Mesh> unitCircle(uint verticesCount,
  //                              float multiplication = 1.0f);
  //  static Ref<Mesh> unitCross(float multiplication = 1.0f);
  //  static Ref<Mesh> unitScaleArrow(float multiplication = 1.0f);
  //  static Ref<Mesh> grid(float size, float step);
  //  static Ref<Mesh> unitArrows(float multiplication = 1.0f);
  //  static Ref<Mesh> unitArrow(float multiplication = 1.0f);
  //  static Ref<Mesh> fromVerticesIndices(float *vertices, VNsize vertexCount,
  //                                       VNuint *indices, VNsize indicesCount,
  //                                       Mesh::PrimitiveType
  //                                       targetPrimitiveType);
  //  static Ref<Mesh> fromVertices(float *data, VNsize size,
  //                                Mesh::PrimitiveType targetPrimitiveType);
};

}  // namespace vanadium

#endif  // VANADIUM_MESH_H
