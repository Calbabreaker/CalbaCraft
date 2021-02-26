#include "coordinates.h"

bool isOutsideChunk(const glm::ivec3& blockPos)
{
    return blockPos.x < 0 || blockPos.x >= CHUNK_SIZE || blockPos.y < 0 ||
           blockPos.y >= CHUNK_SIZE || blockPos.z < 0 || blockPos.z >= CHUNK_SIZE;
}

glm::ivec3 globalBlockToChunkPos(const glm::ivec3& blockPos)
{
    // deals with negative
    return {
        blockPos.x < 0 ? ((blockPos.x - CHUNK_SIZE) / CHUNK_SIZE) : (blockPos.x / CHUNK_SIZE),
        blockPos.y < 0 ? ((blockPos.y - CHUNK_SIZE) / CHUNK_SIZE) : (blockPos.y / CHUNK_SIZE),
        blockPos.z < 0 ? ((blockPos.z - CHUNK_SIZE) / CHUNK_SIZE) : (blockPos.z / CHUNK_SIZE),
    };
}

glm::ivec3 globalToLocalBlockPos(const glm::ivec3& blockPos)
{
    return (CHUNK_SIZE + (blockPos & CHUNK_SIZE)) % CHUNK_SIZE;
}

glm::ivec3 localToGlobalBlockPos(const glm::ivec3& blockPos, const glm::ivec3& chunkPos)
{
    return (CHUNK_SIZE * chunkPos) + blockPos;
}

uint32_t localBlockPosToIndex(const glm::ivec3& blockPos)
{
    return static_cast<uint32_t>(
        blockPos.x * CHUNK_SIZE + blockPos.z + (blockPos.y * CHUNK_SIZE * CHUNK_SIZE));
}
