#pragma once

#include "renderer/gl/buffer.h"

class World;

class Chunk
{
public:
    Chunk();

private:
    VertexBuffer m_vertexBuffer;
    IndexBuffer m_indexBuffer;

    friend class World;
};
