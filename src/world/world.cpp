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
    m_player.position = { 0.0f, 0.0f, 1.0f };
}

World::~World()
{
}

void World::onUpdate(float delta)
{
    m_player.update(delta);

    // update chunks if player moved to new one
    glm::ivec3 playerChunkPos = globalBlockToChunkPos(static_cast<glm::ivec3>(m_player.position));
    if (playerChunkPos != m_loadedChunkPosCenter || m_chunks.size() == 0)
    {
        int renderDistance = Config::getSettings().renderDistance;
        // no chunks then make them around the player
        if (m_chunks.size() == 0)
        {
            glm::ivec3 point1 = playerChunkPos - renderDistance;
            glm::ivec3 point2 = playerChunkPos + renderDistance;

            for (int x = point1.x; x < point2.y; x++)
            {
                for (int y = point1.y; y < point2.y; y++)
                {
                    for (int z = point1.z; z < point2.z; z++)
                    {
                        glm::ivec3 chunkPos = { x, y, z };
                        std::shared_ptr<Chunk> newChunk =
                            std::make_shared<Chunk>(this, m_chunkRenderer.newChunkMesh());
                        newChunk->setChunkPos(chunkPos);
                        m_chunks[chunkPos] = newChunk;
                        m_chunkMeshUpdates.insert(chunkPos);
                    }
                }
            }
        }

        m_loadedChunkPosCenter = playerChunkPos;
    }

    // update chunk meshes
    for (const glm::ivec3& chunkPos : m_chunkMeshUpdates)
    {
        auto iter = m_chunks.find(chunkPos);
        CC_ASSERT_MSG(iter != m_chunks.end(), "Cannot regenerate non existing chunk!");

        iter->second->getChunkMesh()->regenerateMesh(iter->second);
    }

    m_chunkMeshUpdates.clear();
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

blockid_t World::getBlock(const glm::ivec3& blockPos, blockid_t notFoundReturn) const
{
    glm::ivec3 chunkPos = globalBlockToChunkPos(blockPos);
    auto iter = m_chunks.find(chunkPos);
    if (iter != m_chunks.end())
        return iter->second->getBlock(globalToLocalBlockPos(blockPos));
    else
        return notFoundReturn;
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
