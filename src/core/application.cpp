#include <glad/glad.h>

#include "application.h"
#include "config.h"
#include "utils/misc.h"

Application* Application::s_instance = nullptr;

Application::Application()
{
    CC_ASSERT_MSG(s_instance == nullptr, "There is already an instance of Application!");
    s_instance = this;

    Config::loadSettings("config_settings.json");
    BlockDatabase::loadData("data/block_data.json");

    m_window = std::make_unique<Window>();
    m_window->setEventCallback(CC_BIND_FUNC(Application::onEvent));

    m_world = new World();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{
    delete m_world;
}

void Application::run()
{
    m_running = true;

    while (m_running)
    {
        float now = static_cast<float>(glfwGetTime());
        float delta = now - m_lastFrameTime;
        m_lastFrameTime = now;

        m_world->onUpdate(delta);

        glClearColor(0.0f, 0.83f, 0.87f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_world->onRender();

        m_window->onUpdate();
    }
}

void Application::onEvent(const Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowClosedEvent>(CC_BIND_FUNC(Application::onWindowClosedEvent));
    dispatcher.dispatch<WindowResizedEvent>(CC_BIND_FUNC(Application::onWindowResizedEvent));
    m_world->onEvent(event);
}

void Application::onWindowClosedEvent(const WindowClosedEvent& /*event*/)
{
    m_running = false;
}

void Application::onWindowResizedEvent(const WindowResizedEvent& event)
{
    glViewport(0, 0, static_cast<int>(event.width), static_cast<int>(event.height));
}
