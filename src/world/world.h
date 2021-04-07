#pragma once

#include <memory>
#include <queue>

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

    blockid_t getBlock(const glm::ivec3& blockPos) const;

private:
    void onWindowResizedEvent(const WindowResizedEvent& event);
    void onKeyPressedEvent(const KeyPressedEvent& event);
    void onMouseMovedEvent(const MouseMovedEvent& event);

    void updateChunkMeshes();

    void setLoadedChunkCenter(const glm::ivec3& centerPosToSet);

private:
    ChunkPositionMap<std::shared_ptr<Chunk>> m_chunks;
    std::queue<glm::ivec3> m_chunkMeshUpdates;

    Player m_player;
    Camera m_camera;
    ChunkRenderer m_chunkRenderer;

    glm::ivec3 m_loadedChunksPosCenter = {1000.0f, 1000.0f, 1000.0f};
};
