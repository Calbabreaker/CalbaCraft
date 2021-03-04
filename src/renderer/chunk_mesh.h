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
    struct FaceParams
    {
        FaceParams(glm::ivec3& bp, Direction& d) : blockPos(bp), direction(d) {}
        glm::ivec3& blockPos;
        Direction& direction;
        glm::vec2 uvMin;
        glm::vec2 uvMax;
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
    };

public:
    ChunkMesh(ChunkRenderer* chunkRenderer);

    void render();

    void regenerateMesh(const Chunk& chunk);
    void addFace(const FaceParams& params);

    const glm::ivec3& getChunkPos() { return m_chunkPos; }

public:
    static const size_t MAX_VERTICES = CHUNK_VOLUME / 2 * 6 * 4;
    static const uint32_t MAX_INDICES_COUNT = CHUNK_VOLUME / 2 * 6 * 6;

private:
    VertexArray m_vertexArray;
    IndexBuffer m_indexBuffer;
    VertexBuffer m_vertexBuffer;

    Vertex* m_vertexBufferBase;
    Vertex* m_vertexBufferPtr;
    uint32_t m_indicesCount = 0;
    glm::ivec3 m_chunkPos;

    ChunkRenderer* m_chunkRenderer;
};
