#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "application.h"
#include "renderer/camera.h"
#include "renderer/gl/shader.h"
#include "renderer/gl/texture.h"
#include "renderer/gl/vertex_array.h"
#include "utils/misc.h"
#include "world/player.h"

Application* Application::s_instance = nullptr;

Application::Application()
{
    CC_ASSERT_MSG(s_instance == nullptr, "There is already an instance of Application!");
    s_instance = this;

    m_window = std::make_unique<Window>();
    m_window->setEventCallback(CC_BIND_FUNC(Application::onEvent));

    m_camera.setViewportSize(m_window->getWidth(), m_window->getHeight());
    m_player.position = { 0.0f, 0.0f, 1.0f };

    m_window->setMouseLocked(true);
}

Application::~Application()
{
}

void Application::run()
{
    m_running = true;

    Shader shader("shaders/test_vert.glsl", "shaders/test_frag.glsl");
    shader.bind();
    shader.setInt1("u_texture", 0);

    Texture texture("textures/blocks.png");
    texture.bind();

    // clang-format off
    std::vector<float> vertices = {
        -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 
         0.5f,  0.5f, 0.0f,    1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,    1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,    0.0f, 1.0f
    };

    std::vector<uint32_t> indices = { 
        0, 1, 2, 
        2, 3, 0 
    };
    // clang-format on

    VertexArray vertexArray;

    VertexBuffer vertexBuffer(vertices.data(), vertices.size() * sizeof(float));
    BufferElement bufferElements[] = { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } };
    vertexArray.addVertexBuffer(vertexBuffer, bufferElements, 2);

    IndexBuffer indexBuffer(indices.data(), static_cast<uint32_t>(indices.size()));
    vertexArray.setIndexBuffer(indexBuffer);

    while (m_running)
    {
        float now = static_cast<float>(glfwGetTime());
        float delta = now - m_lastFrameTime;
        m_lastFrameTime = now;

        m_player.update(delta);

        glClearColor(0.0f, 0.83f, 0.87f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_camera.update(m_player);
        shader.setMatrix4("u_viewProjection", m_camera.getViewProjection());

        glDrawElements(
            GL_TRIANGLES, static_cast<int>(indexBuffer.getCount()), GL_UNSIGNED_INT, nullptr);

        m_window->onUpdate();
    }
}

void Application::onEvent(const Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowClosedEvent>(CC_BIND_FUNC(Application::onWindowClosedEvent));
    dispatcher.dispatch<WindowResizedEvent>(CC_BIND_FUNC(Application::onWindowResizedEvent));
    dispatcher.dispatch<KeyPressedEvent>(CC_BIND_FUNC(Application::onKeyPressedEvent));
    dispatcher.dispatch<MouseMovedEvent>(CC_BIND_FUNC(Application::onMouseMovedEvent));
}

void Application::onWindowClosedEvent(const WindowClosedEvent& /*event*/)
{
    m_running = false;
}

void Application::onWindowResizedEvent(const WindowResizedEvent& event)
{
    glViewport(0, 0, static_cast<int>(event.width), static_cast<int>(event.height));
    m_camera.setViewportSize(event.width, event.height);
}

void Application::onKeyPressedEvent(const KeyPressedEvent& event)
{
    if (event.key == GLFW_KEY_ESCAPE)
        m_window->setMouseLocked(!m_window->isMouseLocked());
}

void Application::onMouseMovedEvent(const MouseMovedEvent& event)
{
    if (m_window->isMouseLocked())
        m_player.onMouseMoved(event.offset);
}
