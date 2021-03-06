#include "buffer.h"

VertexBuffer::VertexBuffer()
{
    glCreateBuffers(1, &m_handle);
}

VertexBuffer::VertexBuffer(size_t size)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(size), nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VertexBuffer::setDynamicData(const void* data, size_t size)
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<uint32_t>(size), data);
}

void VertexBuffer::setStaticData(const void* data, size_t size)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(size), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer()
{
    glCreateBuffers(1, &m_handle);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void IndexBuffer::setIndices(const uint32_t* indices, uint32_t count)
{
    bind();
    m_count = count;
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<uint32_t>(count * sizeof(uint32_t)),
        indices,
        GL_STATIC_DRAW);
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
