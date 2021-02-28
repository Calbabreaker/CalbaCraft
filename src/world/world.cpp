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
    m_player.position = { 0.0f, 0.0f, 1.0f };
}

World::~World()
{
}

void World::onUpdate(float delta)
{
    m_player.update(delta);

    // update chunks if player moved to new one
    regenerateChunksNeccesery();

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

void World::regenerateChunksNeccesery()
{
    glm::ivec3 playerChunkPos =
        globalBlockToChunkPos(static_cast<glm::ivec3>(m_player.position) * 2);
    if (playerChunkPos != m_loadedChunkPosCenter || m_chunks.size() == 0)
    {
        // no chunks then make them around the player
        if (m_chunks.size() == 0)
        {
            const int& renderDistance = Config::getSettings().renderDistance;
            glm::ivec3 minPoint = playerChunkPos - renderDistance;
            glm::ivec3 maxPoint = playerChunkPos + renderDistance + 1;

            for (int x = minPoint.x; x < maxPoint.y; x++)
            {
                for (int y = minPoint.y; y < maxPoint.y; y++)
                {
                    for (int z = minPoint.z; z < maxPoint.z; z++)
                    {
                        glm::ivec3 chunkPos = { x, y, z };
                        std::shared_ptr<Chunk> newChunk =
                            std::make_shared<Chunk>(this, m_chunkRenderer.newChunkMesh());
                        newChunk->setChunkPos(chunkPos);
                        m_chunkMeshUpdates.insert(chunkPos);
                        m_chunks[chunkPos] = newChunk;
                    }
                }
            }
        }
        else
        {
            // move the chunks to the new pos
            glm::ivec3 chunksMoved = playerChunkPos - m_loadedChunkPosCenter;
            glm::ivec3 chunksMovedAbsVec = glm::abs(chunksMoved);
            glm::ivec3 chunkGrabDirVec = glm::sign(chunksMoved);
            moveChunksAtAxis(0, chunksMovedAbsVec.x, chunkGrabDirVec.x, playerChunkPos);
            moveChunksAtAxis(1, chunksMovedAbsVec.y, chunkGrabDirVec.y, playerChunkPos);
            moveChunksAtAxis(2, chunksMovedAbsVec.z, chunkGrabDirVec.z, playerChunkPos);
        }

        m_loadedChunkPosCenter = playerChunkPos;
    }
}

void World::moveChunksAtAxis(
    const int& axisIndex,
    const int& chunksMovedAbs,
    const int& chunkGrabDir,
    const glm::ivec3& playerChunkPos)
{
    const int& renderDistance = Config::getSettings().renderDistance;
    int numberOfTimesToMove = glm::max(renderDistance - chunksMovedAbs, 0);

    // moves the entire 'face' of chunks amount of times needed
    for (int axisValue = renderDistance; axisValue > numberOfTimesToMove; axisValue--)
    {
        for (int axisValue2 = -renderDistance; axisValue2 <= renderDistance; axisValue2++)
        {
            for (int axisValue3 = -renderDistance; axisValue3 <= renderDistance; axisValue3++)
            {
                glm::ivec3 chunkPosOffset;
                int* posPointer = glm::value_ptr(chunkPosOffset);
                posPointer[(axisIndex + 1) % 3] = axisValue2;
                posPointer[(axisIndex + 2) % 3] = axisValue3;

                posPointer[axisIndex] = -axisValue * chunkGrabDir;
                glm::ivec3 chunkToMovePos = m_loadedChunkPosCenter + chunkPosOffset;

                posPointer[axisIndex] = axisValue * chunkGrabDir;
                glm::ivec3 chunkDestPos = playerChunkPos + chunkPosOffset;

                const std::shared_ptr<Chunk>& chunkToMove = m_chunks[chunkToMovePos];
                chunkToMove->setChunkPos(chunkDestPos);
                m_chunkMeshUpdates.insert(chunkDestPos);

                m_chunks[chunkDestPos] = chunkToMove;
                m_chunks.erase(chunkToMovePos);
            }
        }
    }
}
