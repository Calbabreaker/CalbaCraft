#include "coordinates.h"

chunkpos_t globalBlockToChunkPos(const blockpos_t& blockPos)
{
    // deals with negative
    return {
        blockPos.x < 0 ? ((blockPos.x - CHUNK_SIZE) / CHUNK_SIZE) : (blockPos.x / CHUNK_SIZE),
        blockPos.y < 0 ? ((blockPos.y - CHUNK_SIZE) / CHUNK_SIZE) : (blockPos.y / CHUNK_SIZE),
        blockPos.z < 0 ? ((blockPos.z - CHUNK_SIZE) / CHUNK_SIZE) : (blockPos.z / CHUNK_SIZE),
    };
}

blockpos_t globalToLocalBlockPos(const blockpos_t& blockPos)
{
    // deals with negative
    return { (CHUNK_SIZE + (blockPos.x % CHUNK_SIZE)) % CHUNK_SIZE,
             (CHUNK_SIZE + (blockPos.y % CHUNK_SIZE)) % CHUNK_SIZE,
             (CHUNK_SIZE + (blockPos.z % CHUNK_SIZE)) % CHUNK_SIZE };
}

blockpos_t localToGlobalBlockPos(const blockpos_t& blockPos, const chunkpos_t& chunkPos)
{
    return { blockPos.x + CHUNK_SIZE * chunkPos.x,
             blockPos.y + CHUNK_SIZE * chunkPos.y,
             blockPos.z + CHUNK_SIZE * chunkPos.z };
}

uint32_t localBlockPosToIndex(const blockpos_t& position)
{
    return position.x * CHUNK_SIZE + position.z + (position.y * CHUNK_SIZE * CHUNK_SIZE);
}
