#pragma once

#include <bgfx/bgfx.h>

#include <string>

namespace vanadium {

class ShaderFactory final {
 private:
  static const bgfx::Memory *readFromVfs(const std::string &path);

 public:
  static bgfx::ShaderHandle loadShader(const std::string &path,
                                       const std::string &name);
};

}  // namespace vanadium
