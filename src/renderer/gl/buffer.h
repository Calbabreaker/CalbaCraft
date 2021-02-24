#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(size_t size);
    ~VertexBuffer();

    void bind() const;

    void setDynamicData(const void* data, size_t size);
    void setStaticData(const void* data, size_t size);

private:
    uint32_t m_handle;
};

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void bind() const;

    void setIndices(const uint32_t* indices, uint32_t count);

    uint32_t getCount() const { return m_count; }

private:
    uint32_t m_handle;
    uint32_t m_count;
};

struct BufferElement
{
    GLenum dataType;
    uint32_t magnitude;
};

uint32_t getDataTypeSize(GLenum dataType);
