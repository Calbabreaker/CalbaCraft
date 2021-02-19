#pragma once

#include <memory>

#include "chunk.h"
#include "coordinates.h"
#include "player.h"
#include "renderer/camera.h"
#include "renderer/gl/shader.h"
#include "renderer/gl/texture.h"

class World
{
public:
    World();
    ~World();

    void onUpdate(float delta);
    void onRender();

private:
    ChunkPositionMap<std::shared_ptr<Chunk>> m_chunks;

    Shader m_chunkShader;
    TextureAtlas m_chunkTexture;

    Player m_player;
    Camera m_camera;
};
