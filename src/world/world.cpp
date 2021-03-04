#include <glm/gtc/type_ptr.hpp>

#include "core/application.h"
#include "core/config.h"
#include "core/window.h"
#include "utils/misc.h"

#include "world.h"

World::World()
{
    Window& window = Application::get().getWindow();
    window.setMouseLocked(true);
    m_camera.setViewportSize(window.getWidth(), window.getHeight());
    m_camera.fov = glm::radians(Config::getSettings().fov);
    setLoadedChunkCenter({ 0, 0, 0 });
}

World::~World()
{
}

void World::onUpdate(float delta)
{
    m_player.update(delta);

    // update chunks if player moved to new one
    glm::ivec3 playerChunkPos =
        globalBlockToChunkPos(static_cast<glm::ivec3>(m_player.position) * 2);
    if (m_loadedChunksPosCenter != playerChunkPos)
    {
        setLoadedChunkCenter(playerChunkPos);
    }

    updateChunkMeshes();
}

void World::onRender()
{
    m_camera.update(m_player);
    m_chunkRenderer.render(m_camera);
}

void World::onEvent(const Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowResizedEvent>(CC_BIND_FUNC(World::onWindowResizedEvent));
    dispatcher.dispatch<KeyPressedEvent>(CC_BIND_FUNC(World::onKeyPressedEvent));
    dispatcher.dispatch<MouseMovedEvent>(CC_BIND_FUNC(World::onMouseMovedEvent));
}

blockid_t World::getBlock(const glm::ivec3& blockPos) const
{
    glm::ivec3 chunkPos = globalBlockToChunkPos(blockPos);
    auto iter = m_chunks.find(chunkPos);
    if (iter != m_chunks.end())
        return iter->second->getBlock(globalToLocalBlockPos(blockPos));
    else
        return 0;
}

void World::onWindowResizedEvent(const WindowResizedEvent& event)
{
    m_camera.setViewportSize(event.width, event.height);
}

void World::onKeyPressedEvent(const KeyPressedEvent& event)
{
    Window& window = Application::get().getWindow();
    if (event.key == GLFW_KEY_ESCAPE)
        window.setMouseLocked(!window.isMouseLocked());
}

void World::onMouseMovedEvent(const MouseMovedEvent& event)
{
    Window& window = Application::get().getWindow();
    if (window.isMouseLocked())
        m_player.onMouseMoved(event.offset);
}

void World::updateChunkMeshes()
{
    if (!m_chunkMeshUpdates.empty())
    {
        const glm::ivec3& chunkPos = m_chunkMeshUpdates.front();
        auto iter = m_chunks.find(chunkPos);

        if (iter != m_chunks.end())
            iter->second->regenerate();

        m_chunkMeshUpdates.pop();
    }
}

void World::setLoadedChunkCenter(const glm::ivec3& centerPosToSet)
{
    const int& renderDistance = Config::getSettings().renderDistance;

    std::queue<glm::ivec3> neededChunksPos;
    glm::ivec3 toSetStartPoint = centerPosToSet - renderDistance;
    glm::ivec3 toSetEndPoint = centerPosToSet + (renderDistance + 1);
    for (int x = toSetStartPoint.x; x < toSetEndPoint.x; x++)
    {
        for (int y = toSetStartPoint.y; y < toSetEndPoint.y; y++)
        {
            for (int z = toSetStartPoint.z; z < toSetEndPoint.z; z++)
            {
                glm::ivec3 chunkPos = { x, y, z };
                auto iter = m_chunks.find(chunkPos);
                if (iter == m_chunks.end())
                    neededChunksPos.emplace(chunkPos);
            }
        }
    }

    glm::ivec3 centerStartPoint = m_loadedChunksPosCenter - renderDistance;
    glm::ivec3 centerEndPoint = m_loadedChunksPosCenter + (renderDistance + 1);
    for (int x = centerStartPoint.x; x < centerEndPoint.x; x++)
    {
        for (int y = centerStartPoint.y; y < centerEndPoint.y; y++)
        {
            for (int z = centerStartPoint.z; z < centerEndPoint.z; z++)
            {
                glm::ivec3 chunkPos = { x, y, z };

                // check out of bounds of player chunk position
                if (chunkPos.x < toSetStartPoint.x || chunkPos.x >= toSetEndPoint.x ||
                    chunkPos.y < toSetStartPoint.y || chunkPos.y >= toSetEndPoint.y ||
                    chunkPos.z < toSetStartPoint.z || chunkPos.z >= toSetEndPoint.z)
                {
                    CC_ASSERT_MSG(!neededChunksPos.empty(), "Too many spare chunks!");
                    const glm::ivec3& neededChunkPos = neededChunksPos.front();

                    auto iter = m_chunks.find(chunkPos);
                    if (iter != m_chunks.end())
                    {
                        iter->second->setChunkPos(neededChunkPos);
                        m_chunks[neededChunkPos] = iter->second;
                        m_chunks.erase(chunkPos);
                    }
                    else
                    {
                        std::shared_ptr chunk =
                            std::make_shared<Chunk>(this, m_chunkRenderer.newChunkMesh());
                        chunk->setChunkPos(neededChunkPos);
                        m_chunks[neededChunkPos] = chunk;
                    }

                    m_chunkMeshUpdates.emplace(neededChunkPos);
                    neededChunksPos.pop();
                }
            }
        }
    }

    m_loadedChunksPosCenter = centerPosToSet;
}
