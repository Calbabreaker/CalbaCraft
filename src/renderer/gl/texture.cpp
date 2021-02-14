#include "texture.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string_view filepath)
{
    int width, height;
    stbi_uc* data = stbi_load(filepath.data(), &width, &height, nullptr, 4);
    CC_ASSERT_MSG(data, "Failed to load image at {0}!", filepath);

    m_width = static_cast<uint32_t>(width);
    m_height = static_cast<uint32_t>(height);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
    glTextureStorage2D(m_handle, 1, GL_RGBA8, width, height);

    glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_handle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

void Texture::bind(uint32_t slot)
{
    glBindTextureUnit(slot, m_handle);
}
