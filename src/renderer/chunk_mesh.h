#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "gl/buffer.h"
#include "gl/vertex_array.h"
#include "world/coordinates.h"

class Chunk;
class ChunkRenderer;

class ChunkMesh
{
public:
    ChunkMesh(ChunkRenderer* chunkRenderer);

    void rengenerateMesh(const std::shared_ptr<Chunk>& chunk);
    void render();

public:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
    };

    static const size_t MAX_VERTICES = CHUNK_VOLUME / 2 * 6 * 4 * sizeof(Vertex);
    static const uint32_t MAX_INDICES_COUNT = CHUNK_VOLUME / 2 * 6 * 6;

private:
    VertexArray m_vertexArray;
    IndexBuffer m_indexBuffer;
    VertexBuffer m_vertexBuffer;

    Vertex* vertexBufferBase;
    Vertex* vertexBufferPtr;
    uint32_t indicesCount;

    ChunkRenderer* m_chunkRenderer;
};
