#ifndef VANADIUM_TYPES_H
#define VANADIUM_TYPES_H

#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace Vanadium
{

#ifdef VANADIUM_RENDERAPI_OPENGL
#include "../platform/opengl/OpenGLIncludes.h"

using VNint = GLint;
using VNuint = GLuint;
using VNfloat = GLfloat;
using VNdouble = GLdouble;
using VNbyte = GLbyte;
using VNubyte = GLubyte;
using VNchar = GLchar;
using VNbool = GLboolean;
#else
#error "Unsupported render api."
#endif
using VNsize = size_t;
using VNenum = unsigned long;
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args &&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

enum class DataTypes
{
    Byte = 0,
    UByte,
    Char,
    UInt,
    Int,
    Int2,
    Int3,
    Int4,
    Size,
    Float,
    Float2,
    Float3,
    Float4,
    Double,
    Mat3,
    Mat4,
    Bool,
};

static VNsize dataTypeToSize(DataTypes dataType)
{
    switch (dataType)
    {
        case DataTypes::UByte: return sizeof(VNubyte);
        case DataTypes::Byte: return sizeof(VNbyte);
        case DataTypes::Char: return sizeof(VNchar);
        case DataTypes::UInt: return sizeof(VNuint);
        case DataTypes::Int: return sizeof(VNint);
        case DataTypes::Int2: return sizeof(VNint) * 2;
        case DataTypes::Int3: return sizeof(VNint) * 3;
        case DataTypes::Int4: return sizeof(VNint) * 4;
        case DataTypes::Size: return sizeof(VNsize);
        case DataTypes::Float: return sizeof(VNfloat);
        case DataTypes::Float2: return sizeof(VNfloat) * 2;
        case DataTypes::Float3: return sizeof(VNfloat) * 3;
        case DataTypes::Float4: return sizeof(VNfloat) * 4;
        case DataTypes::Double: return sizeof(VNdouble);
        case DataTypes::Mat3: return sizeof(VNfloat) * 3 * 3;
        case DataTypes::Mat4: return sizeof(VNfloat) * 4 * 4;
        case DataTypes::Bool: return sizeof(VNbool);
        default: return 0;
    }
}

}
#endif //VANADIUM_TYPES_H
