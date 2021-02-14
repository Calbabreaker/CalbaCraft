#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <string_view>

#include "event.h"

class Window
{
public:
    using EventCallbackFunc = std::function<void(const Event&)>;

    Window(
        uint32_t width = 1280, uint32_t height = 720, const std::string_view title = "CalbaCraft");
    ~Window();

    void onUpdate();

    uint32_t getWidth() const { return m_data.width; }
    uint32_t getHeight() const { return m_data.height; }
    GLFWwindow* getHandle() const { return m_handle; }

    void setEventCallback(const EventCallbackFunc& func);

    void setMouseLocked(bool isLocked);
    bool isMouseLocked() const { return m_isMouseLocked; }

private:
    GLFWwindow* m_handle;

    struct WindowData
    {
        uint32_t width, height;
        std::string_view title;
        EventCallbackFunc eventCallback;

        glm::vec2 lastMousePos = { 0.0f, 0.0f };
    };

    WindowData m_data;

    bool m_isMouseLocked = false;
};
