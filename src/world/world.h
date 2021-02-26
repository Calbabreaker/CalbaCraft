#pragma once

#include <memory>

#include "chunk.h"
#include "coordinates.h"
#include "player.h"
#include "renderer/camera.h"
#include "renderer/chunk_renderer.h"

class World
{
public:
    World();
    ~World();

    void onUpdate(float delta);
    void onRender();
    void onEvent(const Event& event);

    blockid_t getBlock(const glm::ivec3& blockPos, blockid_t notFoundReturn = 0) const;

private:
    void onWindowResizedEvent(const WindowResizedEvent& event);
    void onKeyPressedEvent(const KeyPressedEvent& event);
    void onMouseMovedEvent(const MouseMovedEvent& event);

private:
    ChunkPositionMap<std::shared_ptr<Chunk>> m_chunks;
    std::unordered_set<glm::ivec3, ChunkPositionHashKey> m_chunkMeshUpdates;

    Player m_player;
    Camera m_camera;
    ChunkRenderer m_chunkRenderer;

    glm::ivec3 m_loadedChunkPosCenter;
};
