#include "world.h"

#include "chunk.h"

Chunk::Chunk(World* world, const std::shared_ptr<ChunkMesh>& mesh)
    : m_world(world), m_chunkMesh(mesh)
{
}

void Chunk::setChunkPos(const glm::ivec3& chunkPos)
{
    m_chunkPos = chunkPos;

    // load from saved or generate new terrain
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            glm::vec3 globalBlockPos = localToGlobalBlockPos({ x, 0, z }, m_chunkPos);
            int trigY = static_cast<int>(
                glm::sin(globalBlockPos.x / 10.0f) * glm::cos(globalBlockPos.z / 10.0f) * 10.0f +
                10.0f);
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                if (chunkPos.y * CHUNK_SIZE + y < trigY)
                    setBlock({ x, y, z }, 1);
            }
        }
    }
}

void Chunk::setBlock(const glm::ivec3& blockPos, blockid_t id)
{
    m_blocks[localBlockPosToIndex(blockPos)] = id;
}

blockid_t Chunk::getBlock(const glm::ivec3& blockPos, blockid_t notFoundReturn) const
{
    if (isOutsideChunk(blockPos))
        return m_world->getBlock(localToGlobalBlockPos(blockPos, m_chunkPos), notFoundReturn);
    else
        return m_blocks[localBlockPosToIndex(blockPos)];
}
