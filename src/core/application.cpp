#include <glad/glad.h>

#include "application.h"

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

    while (m_running)
    {
        glClearColor(0.0f, 0.83f, 0.87f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_window->onUpdate();
    }
}