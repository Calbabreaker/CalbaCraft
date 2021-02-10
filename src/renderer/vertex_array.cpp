#include <glad/glad.h>

#include "vertex_array.h"

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_handle);
    glDeleteBuffers(static_cast<int>(m_vertexBuffers.size()), m_vertexBuffers.data());
    glDeleteBuffers(1, &m_indexBuffer);
}

void VertexArray::bind()
{
    glBindVertexArray(m_handle);
}

void VertexArray::draw()
{
    glDrawElements(GL_TRIANGLES, static_cast<int>(m_indicesCount), GL_UNSIGNED_INT, nullptr);
}

void VertexArray::addVertexBuffer(int magnitude, const std::vector<float>& vertices)
{
    uint32_t vertexBuffer;
    glCreateBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(vertices.size() * sizeof(float)),
                 vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(static_cast<uint32_t>(m_vertexBuffers.size()));
    glVertexAttribPointer(static_cast<uint32_t>(m_vertexBuffers.size()), magnitude, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    m_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::setIndexBuffer(const std::vector<uint32_t>& indices)
{
    glCreateBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<uint32_t>(indices.size() * sizeof(uint32_t)),
                 indices.data(), GL_STATIC_DRAW);
    m_indicesCount = static_cast<uint32_t>(indices.size());
}