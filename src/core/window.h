#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string_view>

#include "event.h"

class Window
{
public:
    using EventCallbackFunc = std::function<void(const Event&)>;

    Window(uint32_t width = 1280, uint32_t height = 720,
           const std::string_view title = "CalbaCraft");
    ~Window();

    void onUpdate();

    uint32_t getWidth() const { return m_data.width; }
    uint32_t getHeight() const { return m_data.height; }
    GLFWwindow* getContext() const { return m_context; }

    void setEventCallback(const EventCallbackFunc& func);

private:
    GLFWwindow* m_context;

    struct WindowData
    {
        uint32_t width, height;
        std::string_view title;
        EventCallbackFunc eventCallback;
    };

    WindowData m_data;
};
