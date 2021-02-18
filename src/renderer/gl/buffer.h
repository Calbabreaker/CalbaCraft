#include <glad/glad.h>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, size_t size);
    VertexBuffer(size_t size);
    ~VertexBuffer();

    void bind() const;

    void setData(const void* data, size_t size);

private:
    uint32_t m_handle;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    void bind() const;

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
