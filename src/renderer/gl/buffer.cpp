#include "buffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(size), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : m_count(count)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<uint32_t>(count * sizeof(uint32_t)),
        indices,
        GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

uint32_t getDataTypeSize(GLenum dataType)
{
    switch (dataType)
    {
    case GL_UNSIGNED_INT:
    case GL_FLOAT: return 4;
    default: CC_ASSERT_MSG(false, "Unknown dataType!"); return 0;
    }
}
