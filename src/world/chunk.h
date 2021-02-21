#pragma once

#include <array>

#include "block_data.h"
#include "chunk_mesh.h"
#include "coordinates.h"

class Chunk
{
public:
    Chunk();

    void setChunkPos(const glm::ivec3& chunkPos);
    void setBlock(const glm::ivec3& blockPos, blockid_t id);

    void rengenerateMesh();
    void render();

private:
    glm::ivec3 m_chunkPos;

    std::array<blockid_t, CHUNK_VOLUME> m_blocks;
    ChunkMesh m_chunkMesh;
};
