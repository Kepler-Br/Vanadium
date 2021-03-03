#ifndef VANADIUM_MESHFACTORY_H
#define VANADIUM_MESHFACTORY_H

#include "../core/Types.h"

namespace Vanadium
{

class Mesh;

class MeshFactory
{
public:
    static Ref<Mesh> plane(VNint bottomLeft, VNint bottomRight, VNint topLeft, VNint topRight);
    static Ref<Mesh> unitPlane();
};

}

#endif //VANADIUM_MESHFACTORY_H
