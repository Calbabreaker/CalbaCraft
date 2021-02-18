#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

constexpr uint32_t CHUNK_SIZE = 32;
constexpr uint32_t CHUNK_VOLUME = 32 * 32 * 32;

using chunkpos_t = glm::ivec3;
using blockpos_t = glm::ivec3;

struct ChunkPositionHashKey
{
    std::size_t operator()(const chunkpos_t& chunkPos) const
    {
        return std::hash<int>()(chunkPos.x) ^ std::hash<int>()(chunkPos.y) ^
               std::hash<int>()(chunkPos.z);
    }

    bool operator()(const chunkpos_t& a, const chunkpos_t& b) const
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

template <typename T>
using ChunkPositionMap = std::unordered_map<chunkpos_t, T, ChunkPositionHashKey>;

chunkpos_t globalBlockToChunkPos(const blockpos_t& blockPos);
blockpos_t globalToLocalBlockPos(const blockpos_t& blockPos);
blockpos_t localToGlobalBlockPos(const blockpos_t& blockPos, const chunkpos_t& chunkPos);
uint32_t localBlockPosToIndex(const blockpos_t& blockPos);
