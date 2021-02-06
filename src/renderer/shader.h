#pragma once

#include <string_view>

class Shader
{
public:
    Shader(const std::string_view vertexPath, const std::string_view fragmentPath);
    ~Shader();

    void bind() const;

private:
    uint32_t m_handle;
};
