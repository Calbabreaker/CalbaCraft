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

private:
    void onWindowResizedEvent(const WindowResizedEvent& event);
    void onKeyPressedEvent(const KeyPressedEvent& event);
    void onMouseMovedEvent(const MouseMovedEvent& event);

private:
    ChunkPositionMap<std::shared_ptr<Chunk>> m_chunks;

    Player m_player;
    Camera m_camera;

    ChunkRenderer m_chunkRenderer;
};
