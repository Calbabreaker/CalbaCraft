#pragma once

#include <memory>

#include "window.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

private:
    void onEvent(const Event& event);
    void onWindowClosedEvent(const WindowClosedEvent& event);

private:
    bool m_running = false;
    std::unique_ptr<Window> m_window;
};
