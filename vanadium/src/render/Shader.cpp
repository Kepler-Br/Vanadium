#include "Shader.h"
#include "../core/Exceptions.h"
#include "../core/Assert.h"
#include "../core/Log.h"
#include "../core/StringHash.h"
#include <sstream>
#include "../vfs/Vfs.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLShader.h"
    using ShaderImpl = Vanadium::OpenGLShader;
#else
    #error "Not a supported API."
#endif

namespace Vanadium
{

std::string Shader::typeToString(Shader::Type shaderType)
{
    switch (shaderType)
    {
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

Shader::Type Shader::stringToType(const std::string &typeName)
{
    size_t hash = hashString(typeName);

    switch (hash)
    {
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

// Todo: Split it into smaller functions.
ShaderMap ShaderFactory::parseShaderAsset(const std::string &asset)
{
    tinyxml2::XMLDocument doc;
    doc.Parse(asset.data(), asset.size());
    if (doc.ErrorID() != tinyxml2::XML_SUCCESS)
    {
        throw ShaderAssetParsingError(
                dynamic_cast<std::stringstream&>
                (std::stringstream()
                << "Error parsing shader asset file. XML error: "
                << doc.ErrorStr() << "."
                ).str());
    }

    tinyxml2::XMLElement *rootNode = doc.RootElement();
    if (std::string(rootNode->Value()) != "Shader")
    {
        throw ShaderAssetParsingError(
                dynamic_cast<std::stringstream&>
                (std::stringstream()
                << "Shader asset has no appropriate root node(<Shader>)."
                ).str());
    }
    RenderApi::Api currentApi = RenderApi::getApi();
    const std::string &apiString = RenderApi::apiToString(currentApi);
    tinyxml2::XMLElement *apiNode = rootNode->FirstChildElement(apiString.c_str());
    if (apiNode == nullptr)
    {
        throw ShaderAssetParsingError(
                dynamic_cast<std::stringstream&>
                (std::stringstream()
                        << "Shader asset has no needed render API(\""
                        << apiString
                        << "\")."
                ).str());
    }
    ShaderMap shaderSources;
    for (tinyxml2::XMLElement* child = apiNode->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        const std::string &shaderTypeString = child->Value();
        Shader::Type shaderType = Shader::stringToType(shaderTypeString);
        const std::string &shaderSource = child->GetText();
        shaderSources[shaderType] = shaderSource;
    }
    return shaderSources;
}


Ref<Shader> ShaderFactory::create(const std::string &assetPath, const std::string &name)
{
    ShaderMap shaderSources;
    VAN_ENGINE_TRACE("Loading shader asset: \"{}\"", assetPath);
    try
    {
        if(!Vfs::exists(assetPath))
            return nullptr;
        const std::string &asset = Vfs::readWhole(assetPath).str();
        Vfs::ErrorCode error = Vfs::getErrorCode();
        if (error != Vfs::ErrorCode::OK)
        {
            throw ShaderAssetParsingError(
                    dynamic_cast<std::stringstream&>
                    (std::stringstream()
                            << "VFS error: "
                            << Vfs::errorCodeToString(error)
                            << "(Code: "
                            << (VNenum)error
                            << ")"
                    ).str());
        }
        shaderSources = ShaderFactory::parseShaderAsset(asset);
        VAN_ENGINE_TRACE("Compiling shader asset: \"{}\"", assetPath);
        return MakeRef<ShaderImpl>(shaderSources, name);
    }
    catch (const ShaderCompilationError &e)
    {
        VAN_ENGINE_ERROR("Shader \"{}\" throws \"{}\" during compilation. Path: \"{}\"", name, e.what(), assetPath);
        return nullptr;
    }
    catch (const ShaderAssetParsingError &e)
    {
        VAN_ENGINE_ERROR("Shader \"{}\" throws \"{}\" during asset parsing. Path: \"{}\"", name, e.what(), assetPath);
        return nullptr;
    }
}

//Ref<Shader> ShaderFactory::create(const std::string &vertex, const std::string &fragment, const std::string &name)
//{
//    ShaderMap shaderSources({
//                        {Shader::Type::Vertex, vertex},
//                        {Shader::Type::Pixel, fragment}
//                    });
//
//    try
//    {
//        return MakeRef<ShaderImpl>(name, shaderSources);
//    }
//    catch (const ShaderCompilationError &e)
//    {
//        VAN_ENGINE_ERROR("Shader \"{}\" throws \"{}\" during compilation.", name, e.what());
//        return nullptr;
//    }
//}

}