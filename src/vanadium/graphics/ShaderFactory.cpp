#include "ShaderFactory.h"

#include "vanadium/core/Log.h"
#include "vanadium/vfs/InputFileStream.h"

namespace vanadium {

const bgfx::Memory* ShaderFactory::readFromVfs(const std::string& path) {
  vfs::InputFileStream stream(path);

  if (!stream) {
    return nullptr;
  }

  auto fileSize = stream.getLength();
  const bgfx::Memory* memory = bgfx::alloc((uint32_t)fileSize + 1);

  stream.read((char*)memory->data, (uint32_t)fileSize);
  memory->data[fileSize - 1] = '\0';
  return memory;
}

bgfx::ShaderHandle ShaderFactory::loadShader(const std::string& path,
                                             const std::string& name) {
  const bgfx::Memory* shaderBin = ShaderFactory::readFromVfs(path);

  if (shaderBin == nullptr) {
    VAN_ENGINE_ERROR("Cannot open file to read shader: {}", path);

    return bgfx::ShaderHandle{bgfx::kInvalidHandle};
  }
  bgfx::ShaderHandle shader = bgfx::createShader(shaderBin);

  bgfx::setName(shader, name.c_str());
  return shader;
}

}  // namespace vanadium
