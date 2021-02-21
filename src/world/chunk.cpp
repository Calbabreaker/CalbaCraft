#include "chunk.h"

Chunk::Chunk()
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

void Chunk::rengenerateMesh()
{
}

void Chunk::render()
{
}
