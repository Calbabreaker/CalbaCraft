#include <glad/glad.h>

#include "window.h"

static void GLFWErrorCallback(int error, const char* description)
{
    CC_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    m_data.width = width;
    m_data.height = height;
    m_data.title = title;

    CC_LOG_INFO("Creating window: {0} ({1} by {2})", m_data.title, m_data.width, m_data.height);

    {
        // initialize glfw
        int success = glfwInit();
        CC_ASSERT_MSG(success, "Could not initialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);
    }

    {
#ifdef CC_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

        // create window
        m_window = glfwCreateWindow(static_cast<int>(m_data.width), static_cast<int>(m_data.height),
                                    m_data.title.c_str(), nullptr, nullptr);
        CC_ASSERT_MSG(m_window, "Could not create window!");

        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1);
    }

    {
        // initialize glad
        int success = gladLoadGL();
        CC_ASSERT_MSG(success, "Failed to initlialize glad!");
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}