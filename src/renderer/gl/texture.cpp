#include "texture.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string_view filepath)
{
    int width, height;
    stbi_uc* data = stbi_load(filepath.data(), &width, &height, nullptr, 4);
    CC_ASSERT_MSG(data, "Failed to load image at {0}!", filepath);

    m_size = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

    glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
    glTextureStorage2D(m_handle, 1, GL_RGBA8, width, height);

    glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_handle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

void Texture::bind(uint32_t slot) const
{
    glBindTextureUnit(slot, m_handle);
}

TextureAtlas::TextureAtlas(const std::string_view filepath, const glm::uvec2& subTextureSize)
    : Texture(filepath), m_subTextureSize(subTextureSize)
{
}

void TextureAtlas::getSubTextureUVs(
    const glm::uvec2& position, glm::vec2* outMinUV, glm::vec2* outMaxUV) const
{
    glm::vec2 toUVCoord = static_cast<glm::vec2>(m_subTextureSize) / static_cast<glm::vec2>(m_size);
    *outMinUV = static_cast<glm::vec2>(position) * toUVCoord;
    *outMaxUV = static_cast<glm::vec2>(position + static_cast<uint32_t>(1)) * toUVCoord;
}
