#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "utils/files.h"

static const char* getShaderName(GLenum type)
{
    switch (type)
    {
    case GL_VERTEX_SHADER: return "vertex";
    case GL_FRAGMENT_SHADER: return "fragment";
    }

    CC_ASSERT_MSG(false, "Unknown shader type");
    return nullptr;
}

static uint32_t compileShader(GLenum type, const std::string& source)
{
    uint32_t shaderID = glCreateShader(type);
    const char* cSource = source.c_str();
    glShaderSource(shaderID, 1, &cSource, nullptr);
    glCompileShader(shaderID);

#if CC_DEBUG
    int isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    CC_ASSERT_MSG(isCompiled, "Failed to compile {0} shader!", getShaderName(type));
#endif
    return shaderID;
}

static void linkProgram(uint32_t program, std::array<uint32_t, 2> shaders)
{
    for (uint32_t shader : shaders)
        glAttachShader(program, shader);

    glLinkProgram(program);
#if CC_DEBUG
    int isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    CC_ASSERT_MSG(isLinked, "Failed to link program!");
#endif

    for (uint32_t shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
}

Shader::Shader(const std::string_view vertexPath, const std::string_view fragmentPath)
{
    m_handle = glCreateProgram();
    uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, loadFileContents(vertexPath));
    uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, loadFileContents(fragmentPath));
    linkProgram(m_handle, { vertexShader, fragmentShader });
}

Shader::~Shader()
{
    glDeleteProgram(m_handle);
}

void Shader::bind() const
{
    glUseProgram(m_handle);
}

void Shader::setFloat1(const std::string_view name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setFloat4(const std::string_view name, const glm::vec4& value)
{
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const std::string_view name, const glm::mat4& value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int Shader::getUniformLocation(const std::string_view name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location = glGetUniformLocation(m_handle, name.data());
#ifdef CC_DEBUG
    if (location == -1)
        CC_LOG_WARN("Uniform '{0}' does not apear to exist!", name);
#endif

    m_uniformLocationCache[name] = location;
    return location;
}
