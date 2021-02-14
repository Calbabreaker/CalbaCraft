#include <glad/glad.h>

#include "window.h"

static void GLFWErrorCallback(int error, const char* description)
{
    CC_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    CC_ASSERT_RELEASE(error != GLFW_VERSION_UNAVAILABLE, "OpenGL version must be at least 4.5!");
}

static void OpenGLMessageCallback(
    unsigned /*source*/,
    unsigned /*type*/,
    unsigned /*id*/,
    unsigned severity,
    int /*length*/,
    const char* message,
    const void* /*userParam*/)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_LOW: CC_LOG_INFO("OpenGL Info: {0}", message); break;
    case GL_DEBUG_SEVERITY_MEDIUM: CC_LOG_WARN("OpenGL Warn: {0}", message); break;
    case GL_DEBUG_SEVERITY_HIGH: CC_LOG_ERROR("OpenGL Error: {0}", message); break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: CC_LOG_TRACE("OpenGL Trace: {0}", message); break;
    default: CC_ASSERT_MSG(false, "Unknown severity level!"); break;
    }
}

Window::Window(uint32_t width, uint32_t height, std::string_view title)
{
    m_data.width = width;
    m_data.height = height;
    m_data.title = title;

#ifdef CC_DEBUG
    CC_LOG_INFO("Creating window: {0} ({1}px by {2}px)", m_data.title, m_data.width, m_data.height);
#endif

    {
        // initialize glfw
        int status = glfwInit();
        CC_ASSERT_MSG(status, "Could not initialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);
    }

    {
        // make glfw use OpenGL 4.5
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if CC_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

        // create window
        m_handle = glfwCreateWindow(
            static_cast<int>(m_data.width),
            static_cast<int>(m_data.height),
            m_data.title.data(),
            nullptr,
            nullptr);
        CC_ASSERT_RELEASE(m_handle, "Could not create window!");

        glfwMakeContextCurrent(m_handle);
        glfwSwapInterval(1);
    }

    {
        // initialize glad
        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        CC_ASSERT_MSG(status, "Failed to initlialize glad!");

        CC_LOG_INFO("OpenGL Info: ");
        CC_LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        CC_LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        CC_LOG_INFO("  Version: {0}", glGetString(GL_VERSION));

#if CC_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glDebugMessageControl(
            GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_handle);
}

void Window::setEventCallback(const EventCallbackFunc& func)
{
    m_data.eventCallback = func;

    glfwSetWindowUserPointer(m_handle, &m_data);

    glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* handle) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

        WindowClosedEvent event;
        data.eventCallback(event);
    });

    glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* handle, int width, int heigth) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

        WindowResizedEvent event(static_cast<uint32_t>(width), static_cast<uint32_t>(heigth));
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(m_handle, [](GLFWwindow* handle, double xPos, double yPos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

        glm::vec2 position = { static_cast<float>(xPos), static_cast<float>(yPos) };
        glm::vec2 offset = position - data.lastMousePos;
        data.lastMousePos = position;

        MouseMovedEvent event(offset);
        data.eventCallback(event);
    });

    glfwSetKeyCallback(
        m_handle, [](GLFWwindow* handle, int key, int /*scancode*/, int action, int /*mods*/) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(handle));

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key);
                data.eventCallback(event);
                break;
            }
            }
        });
}

void Window::setMouseLocked(bool isLocked)
{
    m_isMouseLocked = isLocked;
    glfwSetInputMode(m_handle, GLFW_CURSOR, isLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

    // recenters cursor
    glm::vec2 newCursorPos = { isLocked ? 0 : m_data.width / 2, isLocked ? 0 : m_data.height / 2 };
    glfwSetCursorPos(m_handle, newCursorPos.x, newCursorPos.y);
    m_data.lastMousePos = newCursorPos;
}
