#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>

class Texture
{
public:
    Texture(const std::string_view filepath);
    virtual ~Texture();

    void bind(uint32_t slot = 0) const;

    const glm::uvec2& getSize() const { return m_size; }

protected:
    uint32_t m_handle;
    glm::uvec2 m_size;
};

class TextureAtlas : public Texture
{
public:
    TextureAtlas(const std::string_view filepath, const glm::uvec2& subTextureSize);

    void getSubTextureUVs(
        const glm::uvec2& position, glm::vec2* outMinUV, glm::vec2* outMaxUV) const;

private:
    glm::uvec2 m_subTextureSize;
};
