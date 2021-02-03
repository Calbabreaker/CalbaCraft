#pragma once

#include "window.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

private:
    bool m_running = false;
};