#pragma once

#include <glad/glad.h>

#include "buffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;

    void draw();

    // automatically calculates stride and offset
    void addVertexBuffer(
        const VertexBuffer& vertexBuffer, BufferElement elements[], uint32_t elementCount);
    void setIndexBuffer(const IndexBuffer& indexBuffer);

private:
    uint32_t m_handle;
    uint32_t m_indicesCount;
};
