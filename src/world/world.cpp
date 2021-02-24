#include "world.h"

World::World()
{
    m_chunks[{ 0, 0, 0 }] = std::make_shared<Chunk>(this, m_chunkRenderer.newChunkMesh());

    const std::shared_ptr<Chunk>& chunk = m_chunks[{ 0, 0, 0 }];
    chunk->getChunkMesh()->rengenerateMesh(chunk);
}

World::~World()
{
}

void World::onUpdate(float delta)
{
    m_player.update(delta);
}

void World::onRender()
{
    m_camera.update(m_player);
}
