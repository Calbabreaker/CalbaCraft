#pragma once

#include <string_view>
#include <unordered_map>

class Shader
{
public:
    Shader(const std::string_view vertexPath, const std::string_view fragmentPath);
    ~Shader();

    void bind() const;

    void setFloat1(const std::string_view name, float value);

private:
    int getUniformLocation(const std::string_view name);

private:
    uint32_t m_handle;
    std::unordered_map<std::string_view, int> m_uniformLocationCache;
};
