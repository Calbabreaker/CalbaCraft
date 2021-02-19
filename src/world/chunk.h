#pragma once

#include <array>

#include "block_data.h"
#include "coordinates.h"
#include "renderer/gl/buffer.h"

class Chunk
{
public:
    Chunk();

    void setChunkPos(const glm::ivec3& chunkPos);

    void setBlock(const glm::ivec3& blockPos, blockid_t id);

private:
    glm::ivec3 m_chunkPos;

    std::array<blockid_t, CHUNK_VOLUME> m_blocks;
};
