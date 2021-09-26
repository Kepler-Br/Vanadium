#include "vanadium/scene/Mesh.h"

#include <vector>

#include "vanadium/core/math/Math.h"

namespace vanadium {

Mesh::Mesh(bgfx::IndexBufferHandle indexBuffer,
           bgfx::VertexBufferHandle vertexBuffer,
           Mesh::PrimitiveType targetPrimitiveType)
    : _indexBuffer(indexBuffer),
      _vertexBuffer(vertexBuffer),
      _primitiveType(targetPrimitiveType) {}

Mesh::~Mesh() {
  bgfx::destroy(this->_indexBuffer);
  bgfx::destroy(this->_vertexBuffer);
}

void Mesh::bind(uint8_t stream) noexcept {
  bgfx::setVertexBuffer(stream, this->_vertexBuffer);
  bgfx::setIndexBuffer(this->_indexBuffer);
}

const bgfx::IndexBufferHandle& Mesh::getIndexBuffer() const noexcept {
  return this->_indexBuffer;
}

const bgfx::VertexBufferHandle& Mesh::getVertexBuffer() const noexcept {
  return this->_vertexBuffer;
}

bool Mesh::operator!() {
  return !(bgfx::isValid(this->_indexBuffer) ||
           bgfx::isValid(this->_vertexBuffer));
}

///*
// * Mesh factory.
// */
//
// Ref<Mesh> MeshFactory::wireframePlane(glm::vec2 bottomLeft,
//                                      glm::vec2 bottomRight, glm::vec2
//                                      topLeft, glm::vec2 topRight) {
//  std::vector<float> vboData = {
//      bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y,
//      topRight.x,   topRight.y,   topLeft.x,     topLeft.y,
//  };
//  Ref<VertexBuffer> vbo = VertexBufferFactory::create(
//      vboData.data(), vboData.size() * sizeof(float));
//  vbo->setLayout({{DataTypes::Float2, "Position"}});
//  Ref<IndexBuffer> ibo = IndexBufferFactory::create({0, 1, 1, 2, 2, 3, 3, 0});
//  Ref<VertexArray> vao = VertexArrayFactory::create();
//  vao->setIndexBuffer(ibo);
//  vao->addVertexBuffer(vbo);
//  vao->unbind();
//  return MakeRef<Mesh>(vao, Mesh::PrimitiveType::Lines);
//}
//
// Ref<Mesh> MeshFactory::unitWireframePlane(float multiplication) {
//  float half = 0.5f * multiplication;
//
//  return MeshFactory::wireframePlane({half, half}, {half, -half}, {-half,
//  half},
//                                     {-half, -half});
//}
//
Ref<Mesh> MeshFactory::plane(glm::vec3 bottomLeft, glm::vec3 bottomRight,
                             glm::vec3 topLeft, glm::vec3 topRight) {
  const float one = 1.0f;
  // float4 vboData, float2 UV, float3 normals.
  static const std::vector<float> vertexData = {
      bottomLeft.x,  bottomLeft.y,  bottomLeft.z,  1.0f,  // Vertex
      one,           one,                                 // UV
      0.0f,          0.0f,          one,                  // Normal
      bottomRight.x, bottomRight.y, bottomRight.z, 1.0f,  // Vertex
      one,           0.0f,                                // UV
      0.0f,          0.0f,          one,                  // Normal
      topRight.x,    topRight.y,    topRight.z,    1.0f,  // Vertex
      0.0f,          0.0f,                                // UV
      0.0f,          0.0f,          one,                  // Normal
      topLeft.x,     topLeft.y,     topLeft.z,     1.0f,  // Vertex
      0.0f,          one,                                 // UV
      0.0f,          0.0f,          one,                  // Normal
  };
  static const std::vector<uint16_t> indexes = {
      2, 1, 0,  //
      3, 2, 0,  //
  };

  bgfx::VertexLayout layout;

  layout.begin()
      .add(bgfx::Attrib::Position, 4, bgfx::AttribType::Float)
      .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
      .end();

  bgfx::VertexBufferHandle vertexBuffer = bgfx::createVertexBuffer(
      bgfx::makeRef(vertexData.data(),
                    (uint32_t)vertexData.size() * sizeof(float)),
      layout);

  bgfx::IndexBufferHandle indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(
      indexes.data(), (uint32_t)indexes.size() * sizeof(uint16_t)));

  return MakeRef<Mesh>(indexBuffer, vertexBuffer,
                       Mesh::PrimitiveType::Triangles);
}

Ref<Mesh> MeshFactory::unitPlane(float multiplication) {
  float half = 0.5f * multiplication;

  return MeshFactory::plane({half, half, 0.0f}, {half, -half, 0.0f},
                            {-half, half, 0.0f}, {-half, -half, 0.0f});
}
//
// Ref<Mesh> MeshFactory::unitCube(float multiplication) {
//  float half = 0.5f * multiplication;
//  float offset = half;
//  float one = 1.0f;
//
//  std::vector<float> vertices = {
//      // front
//      -half,
//      -half,
//      offset,
//      1.0f,
//      -half,
//      half,
//      offset,
//      1.0f,
//      half,
//      -half,
//      offset,
//      1.0f,
//      half,
//      half,
//      offset,
//      1.0f,
//      // back
//      -half,
//      -half,
//      -offset,
//      1.0f,
//      -half,
//      half,
//      -offset,
//      1.0f,
//      half,
//      -half,
//      -offset,
//      1.0f,
//      half,
//      half,
//      -offset,
//      1.0f,
//      // left
//      -half,
//      offset,
//      -half,
//      1.0f,
//      -half,
//      offset,
//      half,
//      1.0f,
//      half,
//      offset,
//      -half,
//      1.0f,
//      half,
//      offset,
//      half,
//      1.0f,
//      // right
//      -half,
//      -offset,
//      -half,
//      1.0f,
//      -half,
//      -offset,
//      half,
//      1.0f,
//      half,
//      -offset,
//      -half,
//      1.0f,
//      half,
//      -offset,
//      half,
//      1.0f,
//      // bottom
//      offset,
//      -half,
//      -half,
//      1.0f,
//      offset,
//      -half,
//      half,
//      1.0f,
//      offset,
//      half,
//      -half,
//      1.0f,
//      offset,
//      half,
//      half,
//      1.0f,
//      // up
//      -offset,
//      -half,
//      -half,
//      1.0f,
//      -offset,
//      -half,
//      half,
//      1.0f,
//      -offset,
//      half,
//      -half,
//      1.0f,
//      -offset,
//      half,
//      half,
//      1.0f,
//  };
//
//  std::vector<float> uvs = {
//      // front
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      one,
//      one,
//      // back
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      one,
//      one,
//      // left
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      one,
//      one,
//      // right
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      one,
//      one,
//      // bottom
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      one,
//      one,
//      // up
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      one,
//      one,
//  };
//
//  std::vector<float> normals = {
//      // front
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      // back
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      // left
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      // right
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      // bottom
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      one,
//      0.0f,
//      0.0f,
//      // up
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//      -one,
//      0.0f,
//      0.0f,
//  };
//
//  Ref<VertexBuffer> vbo = VertexBufferFactory::create(
//      &vertices[0], vertices.size() * sizeof(float));
//  vbo->setLayout({{DataTypes::Float4, "a_Position"}});
//
//  Ref<VertexBuffer> uvBO =
//      VertexBufferFactory::create(&uvs[0], uvs.size() * sizeof(float));
//  uvBO->setLayout({{DataTypes::Float2, "a_UV"}});
//
//  Ref<VertexBuffer> normalBO =
//      VertexBufferFactory::create(&normals[0], normals.size() *
//      sizeof(float));
//  normalBO->setLayout({{DataTypes::Float3, "a_Normal"}});
//
//  VNuint iboOffset = 4;
//  Ref<IndexBuffer> ibo = IndexBufferFactory::create({
//      2,
//      1,
//      0,
//      1,
//      2,
//      3,
//      iboOffset + 0,
//      iboOffset + 1,
//      iboOffset + 2,
//      iboOffset + 3,
//      iboOffset + 2,
//      iboOffset + 1,
//      iboOffset * 2 + 0,
//      iboOffset * 2 + 1,
//      iboOffset * 2 + 2,
//      iboOffset * 2 + 3,
//      iboOffset * 2 + 2,
//      iboOffset * 2 + 1,
//      iboOffset * 3 + 2,
//      iboOffset * 3 + 1,
//      iboOffset * 3 + 0,
//      iboOffset * 3 + 1,
//      iboOffset * 3 + 2,
//      iboOffset * 3 + 3,
//      iboOffset * 4 + 2,
//      iboOffset * 4 + 1,
//      iboOffset * 4 + 0,
//      iboOffset * 4 + 1,
//      iboOffset * 4 + 2,
//      iboOffset * 4 + 3,
//      iboOffset * 5 + 0,
//      iboOffset * 5 + 1,
//      iboOffset * 5 + 2,
//      iboOffset * 5 + 3,
//      iboOffset * 5 + 2,
//      iboOffset * 5 + 1,
//  });
//  Ref<VertexArray> vao = VertexArrayFactory::create();
//  vao->addVertexBuffer(vbo);
//  vao->addVertexBuffer(uvBO);
//  vao->addVertexBuffer(normalBO);
//  vao->setIndexBuffer(ibo);
//  vao->unbind();
//  return MakeRef<Mesh>(vao, Mesh::PrimitiveType::Triangles);
//}
//
// Ref<Mesh> MeshFactory::unitCircle(uint verticesCount, float multiplication) {
//  std::vector<float> vertices;
//
//  float angleDelta = M_PI * 2.0f / (float)verticesCount;
//  float angle = 0.0f;
//  for (uint i = 0; i < verticesCount; i++) {
//    float lineDivider = 1.3f;
//    const float cosAngle = std::cos(angle);
//    const float sinAngle = std::sin(angle);
//
//    vertices.push_back(cosAngle * multiplication / lineDivider);
//    vertices.push_back(sinAngle * multiplication / lineDivider);
//    vertices.push_back(cosAngle * multiplication * lineDivider / 2.0f);
//    vertices.push_back(sinAngle * multiplication * lineDivider / 2.0f);
//
//    vertices.push_back(cosAngle * multiplication * lineDivider * 1.2f /
//                       lineDivider);
//    vertices.push_back(sinAngle * multiplication * lineDivider * 1.2f /
//                       lineDivider);
//    vertices.push_back(cosAngle * multiplication * lineDivider * 1.5f /
//                       lineDivider);
//    vertices.push_back(sinAngle * multiplication * lineDivider * 1.5f /
//                       lineDivider);
//
//    vertices.push_back(cosAngle * multiplication);
//    vertices.push_back(sinAngle * multiplication);
//    angle += angleDelta;
//    vertices.push_back(std::cos(angle) * multiplication);
//    vertices.push_back(std::sin(angle) * multiplication);
//  }
//  return MeshFactory::fromVertices(vertices.data(), vertices.size(),
//                                   Mesh::PrimitiveType::Lines);
//}
//
// Ref<Mesh> MeshFactory::unitCross(float multiplication) {
//  const float half = 0.5f;
//  std::vector<float> vertices = {
//      -half, 0.0f,  half, 0.0f,
//
//      0.0f,  -half, 0.0f, half,
//  };
//  for (float &component : vertices) {
//    component *= multiplication;
//  }
//
//  return MeshFactory::fromVertices(vertices.data(), vertices.size(),
//                                   Mesh::PrimitiveType::Lines);
//}
//
// Ref<Mesh> MeshFactory::unitScaleArrow(float multiplication) {
//  const float half = 0.5f;
//  std::vector<float> vertices = {
//      0.0f,  -half, 0.0f, half,
//
//      -0.2f, half,  0.2f, half,
//
//      -0.2f, -half, 0.2f, -half,
//  };
//  for (float &component : vertices) {
//    component *= multiplication;
//  }
//
//  return MeshFactory::fromVertices(vertices.data(), vertices.size(),
//                                   Mesh::PrimitiveType::Lines);
//}
//
// Ref<Mesh> MeshFactory::grid(float size, float step) {
//  std::vector<float> vertices;
//  const float halfSize = size / 2.0f;
//  for (VNint i = 0; i <= (VNint)(size / step); i++) {
//    // Vertical.
//    float x = -halfSize + step * i;
//    float y = -halfSize;
//    vertices.push_back(x);
//    vertices.push_back(y);
//    x = -halfSize + step * i;
//    y = halfSize;
//    vertices.push_back(x);
//    vertices.push_back(y);
//
//    // Horizontal.
//    x = -halfSize;
//    y = -halfSize + step * i;
//    vertices.push_back(x);
//    vertices.push_back(y);
//    x = halfSize;
//    y = -halfSize + step * i;
//    vertices.push_back(x);
//    vertices.push_back(y);
//  }
//  return MeshFactory::fromVertices(vertices.data(), vertices.size(),
//                                   Mesh::PrimitiveType::Lines);
//}
//
// Ref<Mesh> MeshFactory::unitArrows(float multiplication) {
//  std::vector<float> vertices = {
//      0.0f, 0.0f, 0.0f,  0.5f,
//
//      0.0f, 0.0f, 0.5f,  0.0f,
//
//      0.5f, 0.0f, 0.4f,  -0.1f,
//
//      0.5f, 0.0f, 0.4f,  0.1f,
//
//      0.0f, 0.5f, 0.1f,  0.4f,
//
//      0.0f, 0.5f, -0.1f, 0.4f,
//  };
//  for (float &component : vertices) {
//    component *= multiplication;
//  }
//
//  return MeshFactory::fromVertices(vertices.data(), vertices.size(),
//                                   Mesh::PrimitiveType::Lines);
//}
// Ref<Mesh> MeshFactory::unitArrow(float multiplication) {
//  std::vector<float> vertices = {
//      0.0f, 0.0f, 0.0f,  1.0f,
//
//      0.0f, 1.0f, -0.1f, 0.8f,
//
//      0.0f, 1.0f, 0.1f,  0.8f,
//  };
//  for (float &component : vertices) {
//    component *= multiplication;
//  }
//  return MeshFactory::fromVertices(vertices.data(), vertices.size(),
//                                   Mesh::PrimitiveType::Lines);
//}
//
// Ref<Mesh> MeshFactory::fromVertices(float *vertices, VNsize size,
//                                    Mesh::PrimitiveType targetPrimitiveType) {
//  Ref<VertexBuffer> vbo =
//      VertexBufferFactory::create(vertices, size * sizeof(float));
//  vbo->setLayout({{DataTypes::Float2, "a_Position"}});
//  std::vector<VNuint> iboData;
//  iboData.reserve(size);
//  for (VNuint i = 0; i < (VNuint)(size / 2); i++) {
//    iboData.emplace_back(i);
//  }
//  Ref<IndexBuffer> ibo = IndexBufferFactory::create(iboData);
//  Ref<VertexArray> vao = VertexArrayFactory::create();
//  vao->addVertexBuffer(vbo);
//  vao->setIndexBuffer(ibo);
//  vao->unbind();
//  return MakeRef<Mesh>(vao, targetPrimitiveType);
//}
//
// Ref<Mesh> MeshFactory::fromVerticesIndices(
//    float *vertices, VNsize vertexCount, VNuint *indices, VNsize indicesCount,
//    Mesh::PrimitiveType targetPrimitiveType) {
//  Ref<VertexBuffer> vbo =
//      VertexBufferFactory::create(vertices, vertexCount * sizeof(float));
//  vbo->setLayout({{DataTypes::Float2, "a_Position"}});
//  Ref<IndexBuffer> ibo = IndexBufferFactory::create(indices, indicesCount);
//  Ref<VertexArray> vao = VertexArrayFactory::create();
//  vao->addVertexBuffer(vbo);
//  vao->setIndexBuffer(ibo);
//  vao->unbind();
//  return MakeRef<Mesh>(vao, targetPrimitiveType);
//}

}  // namespace vanadium
