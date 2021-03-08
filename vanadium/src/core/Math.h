#ifndef VANADIUM_MATH_H
#define VANADIUM_MATH_H

#include "Types.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Vanadium
{

namespace Math
{

VNfloat lerp(VNfloat from, VNfloat to, VNfloat t);
glm::vec2 lerp(glm::vec2 from, glm::vec2 to, VNfloat t);
glm::vec3 lerp(glm::vec3 from, glm::vec3 to, VNfloat t);
glm::vec4 lerp(glm::vec4 from, glm::vec4 to, VNfloat t);

}

}



#endif //VANADIUM_MATH_H
