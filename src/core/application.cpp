#include <glad/glad.h>

#include "application.h"
#include "renderer/shader.h"

Application::Application()
{
    m_window = std::make_unique<Window>();
}

Application::~Application()
{
}

void Application::run()
{
    m_running = true;

    Shader shader("shaders/test_vert.glsl", "shaders/test_frag.glsl");
    shader.bind();

    // clang-format off
    std::array<float, 8> vertices = {
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f   
    };

    std::array<uint32_t, 6> indices = {
        0, 1, 2,
        2, 3, 0
    };
    // clang-format on

    uint32_t vertexArray;
    glCreateVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    uint32_t vertexBuffer;
    glCreateBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    uint32_t indexBuffer;
    glCreateBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(),
                 GL_STATIC_DRAW);

    while (m_running)
    {
        glClearColor(0.0f, 0.83f, 0.87f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        m_window->onUpdate();
    }
}
