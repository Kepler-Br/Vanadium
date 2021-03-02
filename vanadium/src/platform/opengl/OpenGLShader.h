#ifndef VANADIUM_OPENGLSHADER_H
#define VANADIUM_OPENGLSHADER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "../../render/Shader.h"
#include "OpenGLIncludes.h"

namespace Vanadium
{

class OpenGLShader : public Shader
{
    using ShaderMap = std::unordered_map<Shader::Type, std::string>;

private:
    std::string name;
    GLuint pointer = 0;
    std::unordered_map<std::string, GLint> uniformLocations;

public:
//    OpenGLShader(const std::string &shaderName, const std::string &vertex, const std::string &pixel);
    OpenGLShader(const ShaderMap &shaderSources, const std::string &shaderName);
    ~OpenGLShader();

    void bind() const noexcept override;
    void unbind() const noexcept override;

    VNint getGlobalId(const std::string &name) noexcept override;

    [[nodiscard]]
    void *getRaw() const noexcept override;

    void setGlobalFloat(const std::string &name, VNfloat value) override;
    void setGlobalFloat2(const std::string &name, const glm::vec2 &value) override;
    void setGlobalFloat3(const std::string &name, const glm::vec3 &value) override;
    void setGlobalFloat4(const std::string &name, const glm::vec4 &value) override;
    void setGlobalInt(const std::string &name, VNint value) override;
    void setGlobalUInt(const std::string &name, VNuint value) override;
    void setGlobalMat3(const std::string &name, const glm::mat3 &value) override;
    void setGlobalMat4(const std::string &name, const glm::mat4 &value) override;

    [[nodiscard]]
    const std::string &getName() const noexcept override;

private:
    void compile(const ShaderMap &shaderSources);
    void link(const std::vector<GLuint> &compiledShaderIDs);
    void printLinkLog();
    void printShaderCompileLog(GLuint shaderPointer);
    GLuint compileShaderProgram(const std::string &source, GLenum shaderType);
    void destroyShaderPrograms(const std::vector<GLuint> &shaderProgramIDs) const;
    bool operator!() const noexcept override;

    static GLenum shaderTypeToOpenGLType(Shader::Type type);

};

}

#endif //VANADIUM_OPENGLSHADER_H
