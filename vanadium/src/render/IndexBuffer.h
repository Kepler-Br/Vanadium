#ifndef VANADIUM_INDEXBUFFER_H
#define VANADIUM_INDEXBUFFER_H

#include "../core/Types.h"
#include <vector>

namespace Vanadium
{

class IndexBuffer
{
public:
    virtual void *getRaw() const noexcept = 0;
    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    virtual VNsize getCount() const noexcept = 0;
};

class IndexBufferFactory
{
public:
    static Ref<IndexBuffer> create(const std::vector<VNuint> &data);
    static Ref<IndexBuffer> create(const VNuint *data, VNsize count);
};

}


#endif //VANADIUM_INDEXBUFFER_H
