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

Shader::Shader(const std::string_view vertexPath, const std::string_view fragmentPath)
{
    m_handle = glCreateProgram();
    uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, loadFileContents(vertexPath));
    uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, loadFileContents(fragmentPath));
    glAttachShader(m_handle, vertexShader);
    glAttachShader(m_handle, fragmentShader);

    glLinkProgram(m_handle);
    glValidateProgram(m_handle);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_handle);
}

void Shader::bind() const
{
    glUseProgram(m_handle);
}
