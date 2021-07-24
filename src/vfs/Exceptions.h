#ifndef VANADIUM_VFS_EXCEPTIONS_H
#define VANADIUM_VFS_EXCEPTIONS_H

#include <stdexcept>

namespace vanadium::vfs {

class VfsError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

}  // namespace vanadium::vfs

#endif  // VANADIUM_VFS_EXCEPTIONS_H
