#include "world.h"

#include "chunk.h"

Chunk::Chunk(World* world, const std::shared_ptr<ChunkMesh>& mesh)
    : m_world(world), m_chunkMesh(mesh)
{
}

void Chunk::setChunkPos(const glm::ivec3& chunkPos)
{
    m_blocks = { 0 };
    m_chunkPos = chunkPos;

    // load from saved or generate new terrain
    glm::ivec3 startBlockPos = m_chunkPos * CHUNK_SIZE;
    glm::ivec3 endBlockPos = startBlockPos + CHUNK_SIZE;

    for (int x = startBlockPos.x; x < endBlockPos.x; x++)
    {
        for (int z = startBlockPos.z; z < endBlockPos.z; z++)
        {
            int trigY = static_cast<int>(glm::sin(x / 10.0f) * glm::cos(z / 10.0f) * 10.0f + 10.0f);
            for (int y = startBlockPos.y; y < endBlockPos.y; y++)
            {
                if (y < trigY)
                {
                    CC_ASSERT(y < 20);
                    glm::ivec3 localBlockPos = globalToLocalBlockPos({ x, y, z });
                    setBlock(localBlockPos, 1);
                }
            }
        }
    }
}

void Chunk::setBlock(const glm::ivec3& blockPos, blockid_t id)
{
    CC_ASSERT_MSG(!isOutsideChunk(blockPos), "Failed to set block outside chunk!");
    m_blocks[localBlockPosToIndex(blockPos)] = id;
}

blockid_t Chunk::getBlock(const glm::ivec3& blockPos, blockid_t notFoundReturn) const
{
    if (isOutsideChunk(blockPos))
        return m_world->getBlock(localToGlobalBlockPos(blockPos, m_chunkPos), notFoundReturn);
    else
        return m_blocks[localBlockPosToIndex(blockPos)];
}
