#include "core/application.h"
#include "core/config.h"
#include "core/window.h"
#include "utils/misc.h"

#include "world.h"

World::World()
{
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(this, m_chunkRenderer.newChunkMesh());
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                chunk->setBlock({ x, y, z }, 1);
            }
        }
    }
    // chunk->setBlock({ 0, 0, 0}, 1);
    // chunk->setBlock({ 1, 1, 1}, 1);
    chunk->setChunkPos({ 0, 0, 0 });
    chunk->getChunkMesh()->rengenerateMesh(chunk);
    m_chunks[{ 0, 0, 0 }] = chunk;

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
