#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

constexpr int CHUNK_SIZE = 32;
constexpr int CHUNK_VOLUME = 32 * 32 * 32;

struct ChunkPositionHashKey
{
    std::size_t operator()(const glm::ivec3& chunkPos) const
    {
        return std::hash<int>()(chunkPos.x) ^ std::hash<int>()(chunkPos.y) ^
               std::hash<int>()(chunkPos.z);
    }

    bool operator()(const glm::ivec3& a, const glm::ivec3& b) const
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

template <typename T>
using ChunkPositionMap = std::unordered_map<glm::ivec3, T, ChunkPositionHashKey>;

glm::ivec3 globalBlockToChunkPos(const glm::ivec3& blockPos);
glm::ivec3 globalToLocalBlockPos(const glm::ivec3& blockPos);
glm::ivec3 localToGlobalBlockPos(const glm::ivec3& blockPos, const glm::ivec3& chunkPos);
uint32_t localBlockPosToIndex(const glm::ivec3& blockPos);
