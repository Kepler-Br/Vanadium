#include "OpenGLShader.h"
#include "OpenGLCall.h"
#include "../../core/Log.h"
#include "../../core/exceptions/ShaderCompilationError.h"

#include <glm/gtc/type_ptr.hpp>

namespace Vanadium
{

OpenGLShader::OpenGLShader(const std::string &shaderName, const std::string &vertex, const std::string &fragment)
{
    this->name = shaderName;
    this->compile(vertex, fragment);
}

void OpenGLShader::bind() const noexcept
{
    VAN_ENGINE_TRACE("Binding shader \"{}\"", this->name);
    glUseProgram(this->pointer);
}

void OpenGLShader::unbind() const noexcept
{
    glUseProgram(0);
}

uint32_t OpenGLShader::getGlobalId(const std::string &name) noexcept
{
    GLint uniformLocation;
    const auto &foundUniformLocation = this->uniformLocations.find(name);

    if (foundUniformLocation != this->uniformLocations.end())
        return foundUniformLocation->second;
    uniformLocation = glGetUniformLocation(this->pointer, name.c_str());
    if (uniformLocation == -1)
    {
        VAN_ENGINE_ERROR("Cannot get uniform location with name \"{}\" from shader \"{}\"", name, this->name);
        return uniformLocation;
    }
    this->uniformLocations[name] = uniformLocation;
    VAN_ENGINE_TRACE("Found uniform \"{}\"", name);
    return uniformLocation;
}

void *OpenGLShader::getRaw() const noexcept
{
    return (void *)&this->pointer;
}

void OpenGLShader::setGlobalFloat(const std::string &name, float value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniform1f(uniformLocation, (GLfloat)value));
}

void OpenGLShader::setGlobalFloat2(const std::string &name, const glm::vec2 &value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniform2fv(uniformLocation, 1, glm::value_ptr(value)));
}

void OpenGLShader::setGlobalFloat3(const std::string &name, const glm::vec3 &value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniform3fv(uniformLocation, 1, glm::value_ptr(value)));
}

void OpenGLShader::setGlobalFloat4(const std::string &name, const glm::vec4 &value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniform4fv(uniformLocation, 1, glm::value_ptr(value)));
}

void OpenGLShader::setGlobalInt(const std::string &name, int value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniform1i(uniformLocation, (GLint)value));
}

void OpenGLShader::setGlobalMat3(const std::string &name, const glm::mat3 &value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value)));
}

void OpenGLShader::setGlobalMat4(const std::string &name, const glm::mat4 &value)
{
    const GLint uniformLocation = this->getGlobalId(name);

    glCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value)));
}

const std::string &OpenGLShader::getName() const noexcept
{
    return this->name;
}

void OpenGLShader::compile(const std::string &vertexSource, const std::string &fragmentSource)
{
    GLuint vertexShaderPointer;
    GLuint fragmentShaderPointer;

    this->pointer = glCreateProgram();
    if (this->pointer == 0)
        throw ShaderCompilationError("glCreateProgram returned 0.");
    VAN_ENGINE_TRACE("Compiling vertex shader");
    vertexShaderPointer = OpenGLShader::compileShaderProgram(vertexSource, GL_VERTEX_SHADER);
    glAttachShader(this->pointer, vertexShaderPointer);
    VAN_ENGINE_TRACE("Compiling fragment shader");
    fragmentShaderPointer = OpenGLShader::compileShaderProgram(fragmentSource, GL_FRAGMENT_SHADER);
    glAttachShader(this->pointer, fragmentShaderPointer);
    VAN_ENGINE_TRACE("Linking shader program \"{}\"", this->name);
    this->link(vertexShaderPointer, fragmentShaderPointer);
    glDetachShader(this->pointer, vertexShaderPointer);
    glDeleteShader(vertexShaderPointer);
    glDetachShader(this->pointer, fragmentShaderPointer);
    glDeleteShader(fragmentShaderPointer);
}

void OpenGLShader::link(GLuint vertexProgramPointer, GLuint fragmentProgramPointer)
{
    GLint isLinked = GL_FALSE;

    glLinkProgram(this->pointer);
    glGetProgramiv(this->pointer, GL_LINK_STATUS, &isLinked);
    this->printLinkLog();
    if (isLinked == GL_FALSE)
    {
        VAN_ENGINE_ERROR("Error linking shader program with name {}", this->name);
        glDetachShader(this->pointer, vertexProgramPointer);
        glDeleteShader(vertexProgramPointer);
        glDetachShader(this->pointer, fragmentProgramPointer);
        glDeleteShader(fragmentProgramPointer);
        glDeleteProgram(this->pointer);
        throw ShaderCompilationError("Shader linking error.");
    }
}

void OpenGLShader::printLinkLog()
{
    GLint maxLength = 0;
    GLchar *logInfo;

    glGetProgramiv(this->pointer, GL_INFO_LOG_LENGTH, &maxLength);
    logInfo = new GLchar[maxLength];
    logInfo[maxLength - 1] = '\0';
    glGetProgramInfoLog(this->pointer, maxLength, &maxLength, logInfo);
    VAN_ENGINE_INFO("Shader program link log for {}:\n{}", this->name, logInfo);
    delete[] logInfo;
}

void OpenGLShader::printShaderCompileLog(GLuint shaderPointer)
{
    GLint maxLength = 0;
    GLchar *logInfo;

    glGetShaderiv(shaderPointer, GL_INFO_LOG_LENGTH, &maxLength);
    logInfo = new GLchar[maxLength];
    logInfo[maxLength - 1] = '\0';
    glGetShaderInfoLog(shaderPointer, maxLength, &maxLength, logInfo);
    VAN_ENGINE_INFO("Shader compile log for {}:\n{}", this->name, logInfo);
    delete[] logInfo;
}

GLuint OpenGLShader::compileShaderProgram(const std::string &source, GLenum shaderType)
{
    GLuint shaderPointer;
    GLint isCompiled = 0;
    const GLchar *cSource = source.c_str();

    glCallThrow(shaderPointer = glCreateShader(shaderType),
                ShaderCompilationError,
                "glCreateShader returned invalid pointer.");
    glShaderSource(shaderPointer, 1, &cSource, nullptr);

    glCompileShader(shaderPointer);
    glGetShaderiv(shaderPointer, GL_COMPILE_STATUS, &isCompiled);
    this->printShaderCompileLog(shaderPointer);
    if (isCompiled == GL_FALSE)
    {
        glDeleteShader(shaderPointer);
        throw ShaderCompilationError("Shader compilation error.");
    }
    return shaderPointer;
}

}