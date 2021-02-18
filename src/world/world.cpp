#include "world.h"

World::World()
{
    m_vertexArray.setLayout();
    m_chunks[{ 0, 0, 0 }] = std::make_shared<Chunk>();
}

World::~World()
{
}

void World::onUpdate(float delta)
{
}

void onRender()
{
}
