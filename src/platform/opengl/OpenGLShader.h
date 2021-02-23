#ifndef VANADIUM_OPENGLSHADER_H
#define VANADIUM_OPENGLSHADER_H

#include <string>
#include <unordered_map>

#include "../../render/Shader.h"
#include "OpenGLIncludes.h"

namespace Vanadium
{

class OpenGLShader : Shader
{
private:
    std::string name;
    GLuint pointer;
    std::unordered_map<std::string, GLuint> uniformLocations;

public:
    OpenGLShader(const std::string &shaderName, const std::string &vertex, const std::string &fragment);

    void bind() const noexcept override;
    void unbind() const noexcept override;

    uint32_t getGlobalId(const std::string &name) noexcept override;

    void *getRaw() const noexcept override;

    void setGlobalFloat(const std::string &name, float value) override;
    void setGlobalFloat2(const std::string &name, const glm::vec2 &value) override;
    void setGlobalFloat3(const std::string &name, const glm::vec3 &value) override;
    void setGlobalFloat4(const std::string &name, const glm::vec4 &value) override;
    void setGlobalInt(const std::string &name, int value) override;
    void setGlobalMat3(const std::string &name, const glm::mat3 &value) override;
    void setGlobalMat4(const std::string &name, const glm::mat4 &value) override;

    const std::string &getName() const noexcept override;

private:
    void compile(const std::string &vertexSource, const std::string &fragmentSource);
    void link(GLuint vertexProgramPointer, GLuint fragmentProgramPointer);
    void printLinkLog();
    void printShaderCompileLog(GLuint shaderPointer);
    GLuint compileShaderProgram(const std::string &source, GLenum shaderType);
};

}

#endif //VANADIUM_OPENGLSHADER_H
