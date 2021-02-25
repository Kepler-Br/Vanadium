#include "OpenGLShader.h"
#include "OpenGLCall.h"
#include "../../core/Log.h"
#include "../../core/exceptions/ShaderCompilationError.h"
#include "../../core/Assert.h"

#include <glm/gtc/type_ptr.hpp>

namespace Vanadium
{

using ShaderMap = std::unordered_map<Shader::Type, std::string>;

OpenGLShader::OpenGLShader(const std::string &shaderName, const std::string &vertex, const std::string &pixel)
{
    ShaderMap shaderSources(
                        {
                                {Shader::Type::Vertex, vertex},
                                {Shader::Type::Pixel, pixel}
                            });

    this->name = shaderName;
    this->compile(shaderSources);
}

OpenGLShader::OpenGLShader(const std::string &shaderName, const ShaderMap &shaderSources)
{
    this->name = shaderName;
    this->compile(shaderSources);
}


OpenGLShader::~OpenGLShader()
{
    VAN_ENGINE_TRACE("Destroying shader \"{}\".", name);
    glDeleteProgram(this->pointer);
}

void OpenGLShader::bind() const noexcept
{
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

    VAN_ENGINE_TRACE("Getting shader global variable id: {}", name);
    if (foundUniformLocation != this->uniformLocations.end())
        return foundUniformLocation->second;
    uniformLocation = glGetUniformLocation(this->pointer, name.c_str());
    if (uniformLocation == -1)
    {
        VAN_ENGINE_ERROR("Cannot get uniform location with name \"{}\" from shader \"{}\".", name, this->name);
        return uniformLocation;
    }
    this->uniformLocations[name] = uniformLocation;
    return uniformLocation;
}

void *OpenGLShader::getRaw() const noexcept
{
    return (void *)&this->pointer;
}

void OpenGLShader::setGlobalFloat(const std::string &name, VNfloat value)
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

void OpenGLShader::setGlobalInt(const std::string &name, VNint value)
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

void OpenGLShader::compile(const ShaderMap &shaderSources)
{
    std::vector<GLuint> compiledShaderIDs;

    compiledShaderIDs.reserve(shaderSources.size());
    this->pointer = glCreateProgram();
    if (this->pointer == 0)
        throw ShaderCompilationError("glCreateProgram returned 0.");
    for (const auto &shader : shaderSources)
    {
        GLenum shaderType = OpenGLShader::shaderTypeToOpenGLType(shader.first);
        GLuint program;

        VAN_ENGINE_TRACE("Compiling \"{}\" shader.", Shader::typeToString(shader.first));
        program = OpenGLShader::compileShaderProgram(shader.second, shaderType);
        compiledShaderIDs.emplace_back(program);
    }
    VAN_ENGINE_TRACE("Linking shader program \"{}\".", this->name);
    this->link(compiledShaderIDs);
    this->destroyShaderPrograms(compiledShaderIDs);
}

void OpenGLShader::link(const std::vector<GLuint> &compiledShaderIDs)
{
    GLint isLinked = GL_FALSE;

    glLinkProgram(this->pointer);
    glGetProgramiv(this->pointer, GL_LINK_STATUS, &isLinked);
    this->printLinkLog();
    if (isLinked == GL_FALSE)
    {
        VAN_ENGINE_ERROR("Error linking shader program with name {}.", this->name);
        this->destroyShaderPrograms(compiledShaderIDs);
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
    VAN_ENGINE_INFO("Shader program link log for {}:\n{}.", this->name, logInfo);
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
    VAN_ENGINE_INFO("Shader compile log for {}:\n{}.", this->name, logInfo);
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

void OpenGLShader::destroyShaderPrograms(const std::vector<GLuint> &shaderProgramIDs)
{
    for(const auto &program : shaderProgramIDs)
    {
        glDetachShader(this->pointer, program);
        glDeleteShader(program);
    }
}

GLenum OpenGLShader::shaderTypeToOpenGLType(Shader::Type type)
{
    switch (type)
    {
        case Shader::Type::Vertex:
            return GL_VERTEX_SHADER;
        case Shader::Type::Pixel:
            return GL_FRAGMENT_SHADER;
        default:
            VAN_ENGINE_ASSERT(false, "OpenGLShader::shaderTypeToOpenGLType: unknown shader type.");
            return 0;
    }
}

}