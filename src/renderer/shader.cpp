#include <glad/glad.h>

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

    int isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    CC_ASSERT_MSG(isCompiled, "Failed to compile {0} shader!", getShaderName(type));
    return shaderID;
}

static void linkProgram(uint32_t program, std::array<uint32_t, 2> shaders)
{
    for (uint32_t shader : shaders)
        glAttachShader(program, shader);

    glLinkProgram(program);
    int isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    CC_ASSERT_MSG(isLinked, "Failed to link program!");

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