#pragma once

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(uint32_t width = 1280, uint32_t height = 720, const std::string& title = "CalbaCraft");
    ~Window();

    void onUpdate();

private:
    GLFWwindow* m_window;

    struct WindowData
    {
        uint32_t width, height;
        std::string title;
    };

    WindowData m_data;
};