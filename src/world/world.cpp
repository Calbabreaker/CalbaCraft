#include "world.h"

World::World()
    : m_chunkShader("shaders/chunk_vert.glsl", "shaders/chunk_frag.glsl"),
      m_chunkTexture("textures/blocks.png", { 16, 16 })
{
    m_chunks[{ 0, 0, 0 }] = std::make_shared<Chunk>();

    m_chunkShader.bind();
    m_chunkShader.setInt1("u_texture", 0);
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
    m_chunkShader.bind();
    m_chunkShader.setMat4("u_viewProjection", m_camera.getViewProjection());
    m_chunkTexture.bind();

    for (auto& iter : m_chunks)
    {
    }
}
