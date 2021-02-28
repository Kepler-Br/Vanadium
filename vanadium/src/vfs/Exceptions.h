#ifndef VANADIUM_EXCEPTIONS_H
#define VANADIUM_EXCEPTIONS_H

#include <stdexcept>

namespace Vanadium
{

namespace Vfs
{

class VfsError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}

}

#endif //VANADIUM_EXCEPTIONS_H
