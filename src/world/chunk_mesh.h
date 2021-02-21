#pragma once

#include <array>

#include "block_data.h"
#include "coordinates.h"
#include "renderer/gl/buffer.h"
#include "renderer/gl/vertex_array.h"

class ChunkMesh
{
public:
    ChunkMesh();

    void genMesh(const std::array<blockid_t, CHUNK_VOLUME>& blocks);
    void render();

private:
    VertexArray m_vertexArray;
    IndexBuffer m_indexBuffer;
    VertexBuffer m_vertexBuffer;
};
