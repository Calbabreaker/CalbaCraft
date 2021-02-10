#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "application.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"
#include "utils/misc.h"

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

    Shader shader("./shaders/test_vert.glsl", "./shaders/test_frag.glsl");
    shader.bind();
    shader.setFloat4("u_color", { 1.0f, 0.0f, 1.0f, 1.0f });

    glm::vec3 position = { 0.0f, 0.0f, 10.0f };
    glm::vec3 front = { 0.0f, 0.0f, -1.0f };
    glm::vec3 up = { 0.0f, 1.0f, 0.0f };

    float width = static_cast<float>(m_window->getWidth());
    float height = static_cast<float>(m_window->getHeight());
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / height, 0.01f, 1000.0f);

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

        glm::mat4 view = glm::lookAt(position, position + front, up);
        glm::mat4 viewProjection = projection * view;
        shader.setMatrix4("u_viewProjection", viewProjection);
        position.z -= 0.01f;

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
