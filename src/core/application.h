#pragma once

#include <memory>

#include "renderer/camera.h"
#include "window.h"
#include "world/player.h"
#include "world/world.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

    Window& getWindow() { return *m_window; }
    static Application& get() { return *s_instance; }

private:
    void onEvent(const Event& event);
    void onWindowClosedEvent(const WindowClosedEvent& event);
    void onWindowResizedEvent(const WindowResizedEvent& event);
    void onKeyPressedEvent(const KeyPressedEvent& event);
    void onMouseMovedEvent(const MouseMovedEvent& event);

private:
    bool m_running = false;
    float m_lastFrameTime = 0.0f;

    std::unique_ptr<Window> m_window;
    World* m_world;
    static Application* s_instance;

    Player m_player;
    Camera m_camera;
};
