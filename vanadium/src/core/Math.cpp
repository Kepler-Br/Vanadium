#include "Math.h"


namespace Vanadium
{

namespace Math
{

VNfloat lerp(VNfloat from, VNfloat to, VNfloat t)
{
    return from - ((from - to) * t);
}

glm::vec2 lerp(glm::vec2 from, glm::vec2 to, VNfloat t)
{
    return {
            from.x - ((from.x - to.x) * t),
            from.y - ((from.y - to.y) * t),
    };
}

glm::vec3 lerp(glm::vec3 from, glm::vec3 to, VNfloat t)
{
    return {
            from.x - ((from.x - to.x) * t),
            from.y - ((from.y - to.y) * t),
            from.z - ((from.z - to.z) * t),
    };
}

glm::vec4 lerp(glm::vec4 from, glm::vec4 to, VNfloat t)
{
    return {
            from.x - ((from.x - to.x) * t),
            from.y - ((from.y - to.y) * t),
            from.z - ((from.z - to.z) * t),
            from.w - ((from.w - to.w) * t),
    };
}

}

}