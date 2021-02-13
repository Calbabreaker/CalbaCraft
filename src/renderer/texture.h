#pragma once

class Texture
{
public:
    Texture(const std::string_view filepath);
    ~Texture();

    void bind(uint32_t slot);

private:
    uint32_t m_handle;
    uint32_t m_width, m_height;
};
