#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(uint32_t width, uint32_t height);
    ~Window();

    void onUpdate();

private:
};