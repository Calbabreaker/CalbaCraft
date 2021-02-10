#pragma once

#include <vector>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void draw();

    void addVertexBuffer(int magnitude, const std::vector<float>& vertices);
    void setIndexBuffer(const std::vector<uint32_t>& indices);

private:
    uint32_t m_handle;

    std::vector<uint32_t> m_vertexBuffers;
    uint32_t m_indexBuffer;
    uint32_t m_indicesCount;
};