#pragma once

#include <memory>

#include "chunk.h"
#include "coordinates.h"
#include "player.h"
#include "renderer/camera.h"
#include "renderer/gl/vertex_array.h"

class World
{
public:
    World();
    ~World();

    void onUpdate(float delta);
    void onRender();

private:
    ChunkPositionMap<std::shared_ptr<Chunk>> m_chunks;

    VertexArray m_vertexArray;

    Player m_player;
    Camera m_camera;
};
