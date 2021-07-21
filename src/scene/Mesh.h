#ifndef VANADIUM_MESH_H
#define VANADIUM_MESH_H

#include "../core/Types.h"

namespace Vanadium {

//class Mesh {
// public:
//  enum class PrimitiveType {
//    Lines = 0,
//    LineLoop,
//    Triangles,
//  };
//
// protected:
//  Ref<VertexArray> vertexArray = nullptr;
//  PrimitiveType primitiveType;
//
// public:
//  explicit Mesh(PrimitiveType targetPrimitiveType)
//      : primitiveType(targetPrimitiveType) {}
//  Mesh(const Ref<VertexArray> &vertexArray, PrimitiveType targetPrimitiveType);
//  Mesh(const Ref<VertexBuffer> &vertexBuffer,
//       const Ref<IndexBuffer> &indexBuffer, PrimitiveType targetPrimitiveType);
//  virtual ~Mesh() = default;
//
//  void setVertexArray(const Ref<VertexArray> &arr) noexcept;
//  Ref<VertexArray> getVertexArray() noexcept;
//  PrimitiveType getPrimitiveType() noexcept;
//  void setPrimitiveType(PrimitiveType targetPrimitiveType) noexcept;
//  void bind() noexcept;
//  void unbind() noexcept;
//  bool operator!();
//};
//
//class MeshFactory {
// public:
//  static Ref<Mesh> wireframePlane(glm::vec2 bottomLeft, glm::vec2 bottomRight,
//                                  glm::vec2 topLeft, glm::vec2 topRight);
//  static Ref<Mesh> unitWireframePlane(float multiplication = 1.0f);
//  static Ref<Mesh> plane(glm::vec3 bottomLeft, glm::vec3 bottomRight,
//                         glm::vec3 topLeft, glm::vec3 topRight);
//  static Ref<Mesh> unitPlane(float multiplication = 1.0f);
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
//                                       Mesh::PrimitiveType targetPrimitiveType);
//  static Ref<Mesh> fromVertices(float *data, VNsize size,
//                                Mesh::PrimitiveType targetPrimitiveType);
//};

}  // namespace Vanadium

#endif  // VANADIUM_MESH_H
