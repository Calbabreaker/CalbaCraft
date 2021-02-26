#include <glad/glad.h>

#include "vertex_array.h"

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_handle);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_handle);
}

void VertexArray::draw(uint32_t indicesCount)
{
    glDrawElements(
        GL_TRIANGLES,
        static_cast<int>(indicesCount ? indicesCount : m_indicesCount),
        GL_UNSIGNED_INT,
        nullptr);
}

void VertexArray::addVertexBuffer(
    const VertexBuffer& vertexBuffer, BufferElement elements[], uint32_t elementCount)
{
    bind();
    vertexBuffer.bind();

    // calculate stride
    int stride = 0;
    for (uint32_t i = 0; i < elementCount; i++)
        stride += static_cast<int>(getDataTypeSize(elements[i].dataType) * elements[i].magnitude);

    uint32_t offset = 0;
    for (uint32_t i = 0; i < elementCount; i++)
    {
        glEnableVertexAttribArray(i);

        int magnitude = static_cast<int>(elements[i].magnitude);
        GLenum dataType = elements[i].dataType;
        const void* castedOffset = reinterpret_cast<const void*>(offset);

        switch (dataType)
        {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_INT:
        case GL_UNSIGNED_INT:
            glVertexAttribIPointer(i, magnitude, dataType, stride, castedOffset);
            break;
        case GL_FLOAT:
            glVertexAttribPointer(i, magnitude, dataType, GL_FALSE, stride, castedOffset);
            break;
        default: CC_ASSERT_MSG(false, "Unknown dataType!"); break;
        }

        offset += getDataTypeSize(dataType) * elements[i].magnitude;
    }
}

void VertexArray::setIndexBuffer(const IndexBuffer& indexBuffer)
{
    bind();
    indexBuffer.bind();
    m_indicesCount = indexBuffer.getCount();
}
