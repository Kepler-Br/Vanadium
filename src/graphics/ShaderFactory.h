#ifndef VANADIUM_SHADERFACTORY_H
#define VANADIUM_SHADERFACTORY_H

#include <bgfx/bgfx.h>

#include "core/Log.h"
#include "vfs/FileStream.h"

namespace vanadium {

class ShaderFactory {
 private:
  static const bgfx::Memory *readFromVfs(const std::string &path);

 public:
  static bgfx::ShaderHandle loadShader(const std::string &path,
                                       const std::string &name);
};

}  // namespace vanadium

#endif  // VANADIUM_SHADERFACTORY_H
