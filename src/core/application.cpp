#include "application.h"

#include <iostream>

Application::Application()
{
}

Application::~Application()
{
}

void Application::run()
{
    m_running = true;

    std::cout << "Running" << std::endl;

    while (m_running)
    {
    }
}