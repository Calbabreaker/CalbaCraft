#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "application.h"
#include "renderer/camera.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"
#include "utils/misc.h"
#include "world/player.h"

Application::Application()
{
    m_window = std::make_unique<Window>();
    m_window->setEventCallback(CC_BIND_FUNC(Application::onEvent));
}

Application::~Application()
{
}

void Application::run()
{
    m_running = true;

    Player player;
    Camera camera;
    camera.setViewportSize(m_window->getWidth(), m_window->getHeight());

    Shader shader("./shaders/test_vert.glsl", "./shaders/test_frag.glsl");
    shader.bind();
    shader.setFloat4("u_color", { 1.0f, 0.0f, 1.0f, 1.0f });

    // clang-format off
    std::vector<float> vertices = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        2, 3, 0
    };
    // clang-format on

    VertexArray vertexArray;
    vertexArray.bind();
    vertexArray.addVertexBuffer(3, vertices);
    vertexArray.setIndexBuffer(indices);

    while (m_running)
    {
        glClearColor(0.0f, 0.83f, 0.87f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        player.position.z -= 0.01f;
        camera.update(player);

        shader.setMatrix4("u_viewProjection", camera.getViewProjection());

        vertexArray.draw();

        m_window->onUpdate();
    }
}

void Application::onEvent(const Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowClosedEvent>(CC_BIND_FUNC(Application::onWindowClosedEvent));
}

void Application::onWindowClosedEvent(const WindowClosedEvent&)
{
    m_running = false;
}
