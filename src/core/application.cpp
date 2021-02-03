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
        m_window->onUpdate();
    }
}