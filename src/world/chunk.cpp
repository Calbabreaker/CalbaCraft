#include "chunk.h"

Chunk::Chunk(World* world, const std::shared_ptr<ChunkMesh>& mesh)
    : m_world(world), m_chunkMesh(mesh)
{
}

void Chunk::setChunkPos(const glm::ivec3& chunkPos)
{
    m_chunkPos = chunkPos;
}

void Chunk::setBlock(const glm::ivec3& blockPos, blockid_t id)
{
    m_blocks[localBlockPosToIndex(blockPos)] = id;
}

blockid_t Chunk::getBlock(const glm::ivec3& blockPos) const
{
    if (!isOutsideChunk(blockPos))
        return m_blocks[localBlockPosToIndex(blockPos)];
    else
        // TODO: get block from world
        return 0;
}
