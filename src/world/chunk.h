#pragma once

#include <array>
#include <memory>

#include "block_data.h"
#include "coordinates.h"
#include "renderer/chunk_mesh.h"

class World;

class Chunk
{
public:
    Chunk(World* world, const std::shared_ptr<ChunkMesh>& mesh);

    void setChunkPos(const glm::ivec3& chunkPos);
    void setBlock(const glm::ivec3& blockPos, blockid_t id);

    const std::shared_ptr<ChunkMesh>& getChunkMesh() const { return m_chunkMesh; }

private:
    glm::ivec3 m_chunkPos;
    std::array<blockid_t, CHUNK_VOLUME> m_blocks;

    World* m_world;
    std::shared_ptr<ChunkMesh> m_chunkMesh;
};
