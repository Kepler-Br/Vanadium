#include "render/Shader.h"

#include <sstream>

#include "core/Assert.h"
#include "core/Exceptions.h"
#include "core/Log.h"
#include "core/StringHash.h"
#include "vfs/Vfs.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "platform/opengl/OpenGLShader.h"
using ShaderImpl = Vanadium::OpenGLShader;
#endif

namespace Vanadium {

std::string Shader::typeToString(Shader::Type shaderType) {
  switch (shaderType) {
    case Shader::Type::Pixel:
      return std::string("Pixel");
    case Shader::Type::Vertex:
      return std::string("Vertex");
    case Shader::Type::Compute:
      return std::string("Compute");
    case Shader::Type::Geometry:
      return std::string("Geometry");
    case Shader::Type::TesselationControl:
      return std::string("TesselationControl");
    case Shader::Type::TesselationEval:
      return std::string("TesselationEval");
    default:
      VAN_ENGINE_ASSERT(false, "Unknown shader type!");
      return std::string("Unknown");
  }
}

Shader::Type Shader::stringToType(const std::string &typeName) {
  unsigned long hash = hashString(typeName);

  switch (hash) {
    case "Pixel"_hash:
      return Shader::Type::Pixel;
    case "Vertex"_hash:
      return Shader::Type::Vertex;
    case "Compute"_hash:
      return Shader::Type::Compute;
    case "Geometry"_hash:
      return Shader::Type::Geometry;
    case "TesselationControl"_hash:
      return Shader::Type::TesselationControl;
    case "TesselationEval"_hash:
      return Shader::Type::TesselationEval;
    default:
      VAN_ENGINE_ASSERT(false, "Shader::stringToType: unknown shader type.");
      return Shader::Type::Unknown;
  }
}

/*
 * ShaderFactory
 */

using ShaderMap = std::unordered_map<Shader::Type, std::string>;

ShaderMap ShaderFactory::parseShaderAsset(const std::vector<char> &asset) {
  tinyxml2::XMLDocument doc;
  doc.Parse(&asset[0], asset.size());
  if (doc.ErrorID() != tinyxml2::XML_SUCCESS) {
    throw ShaderAssetParsingError(fmt::format(
        "Error parsing shader asset file. XML error: {}.", doc.ErrorStr()));
  }
  tinyxml2::XMLElement *rootNode = doc.RootElement();
  if (std::string(rootNode->Value()) != "Shader") {
    throw ShaderAssetParsingError(
        fmt::format("Shader asset has no appropriate root node(<Shader>)."));
  }
  RenderApi::Api currentApi = RenderApi::getApi();
  const std::string &apiString = RenderApi::apiToString(currentApi);
  tinyxml2::XMLElement *apiNode =
      rootNode->FirstChildElement(apiString.c_str());
  if (apiNode == nullptr) {
    throw ShaderAssetParsingError(fmt::format(
        "Shader asset has no needed render API(\"{}\").", apiString));
  }
  ShaderMap shaderSources;
  for (tinyxml2::XMLElement *child = apiNode->FirstChildElement();
       child != nullptr; child = child->NextSiblingElement()) {
    const std::string &shaderTypeString = child->Value();
    Shader::Type shaderType = Shader::stringToType(shaderTypeString);
    const std::string &shaderSource = child->GetText();
    shaderSources[shaderType] = shaderSource;
  }
  return shaderSources;
}

Ref<Shader> ShaderFactory::create(const std::string &assetPath,
                                  const std::string &name) {
  ShaderMap shaderSources;
  VAN_ENGINE_TRACE("Loading shader asset: \"{}\"", assetPath);
  try {
    if (!Vfs::exists(assetPath)) {
      VAN_ENGINE_ERROR("Shader \"{}\" does not exists.", assetPath);
      return nullptr;
    }
    const std::vector<char> &asset = Vfs::readWhole(assetPath);
    Vfs::ErrorCode error = Vfs::getErrorCode();
    if (error != Vfs::ErrorCode::OK) {
      throw ShaderAssetParsingError(fmt::format("VFS error: {} (Code: {})",
                                                Vfs::errorCodeToString(error),
                                                (VNenum)error));
    }
    shaderSources = ShaderFactory::parseShaderAsset(asset);
    VAN_ENGINE_TRACE("Compiling shader asset: \"{}\"", assetPath);
    return MakeRef<ShaderImpl>(shaderSources, name);
  } catch (const ShaderCompilationError &e) {
    VAN_ENGINE_ERROR(
        "Shader \"{}\" throws \"{}\" during compilation. Path: \"{}\"", name,
        e.what(), assetPath);
    return nullptr;
  } catch (const ShaderAssetParsingError &e) {
    VAN_ENGINE_ERROR(
        "Shader \"{}\" throws \"{}\" during asset parsing. Path: \"{}\"", name,
        e.what(), assetPath);
    return nullptr;
  }
}

}  // namespace Vanadium