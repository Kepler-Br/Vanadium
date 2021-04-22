#ifndef VANADIUM_VFS_EXCEPTIONS_H
#define VANADIUM_VFS_EXCEPTIONS_H

#include <stdexcept>

namespace Vanadium {

namespace Vfs {

class VfsError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

}  // namespace Vfs

}  // namespace Vanadium

#endif  // VANADIUM_VFS_EXCEPTIONS_H
