#include <glad/glad.h>

#include "window.h"

static void GLFWErrorCallback(int error, const char* description)
{
    CC_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    CC_ASSERT_RELEASE(error != GLFW_VERSION_UNAVAILABLE, "OpenGL version must be at least 4.5!");
}

static void OpenGLMessageCallback(unsigned /*source*/, unsigned /*type*/, unsigned /*id*/,
                                  unsigned severity, int /*length*/, const char* message,
                                  const void* /*userParam*/)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_LOW: CC_LOG_INFO("OpenGL Info: {0}", message); return;
    case GL_DEBUG_SEVERITY_MEDIUM: CC_LOG_WARN("OpenGL Warn: {0}", message); return;
    case GL_DEBUG_SEVERITY_HIGH: CC_LOG_ERROR("OpenGL Error: {0}", message); return;
    case GL_DEBUG_SEVERITY_NOTIFICATION: CC_LOG_TRACE("OpenGL Trace: {0}", message); return;
    }

    CC_ASSERT_MSG(false, "Unknown severity level!");
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
        m_context =
            glfwCreateWindow(static_cast<int>(m_data.width), static_cast<int>(m_data.height),
                             m_data.title.data(), nullptr, nullptr);
        CC_ASSERT_RELEASE(m_context, "Could not create window!");

        glfwMakeContextCurrent(m_context);
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

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0,
                              nullptr, GL_FALSE);
#endif
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_context);
    glfwTerminate();
}

void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_context);
}

void Window::setEventCallback(const EventCallbackFunc& func)
{
    m_data.eventCallback = func;

    glfwSetWindowUserPointer(m_context, &m_data);

    glfwSetWindowCloseCallback(m_context, [](GLFWwindow* context) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(context));

        WindowClosedEvent event;
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(m_context, [](GLFWwindow* context, double xPos, double yPos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(context));

        glm::vec2 position = { static_cast<float>(xPos), static_cast<float>(yPos) };
        static glm::vec2 lastMousePos = position;
        glm::vec2 offset = position - lastMousePos;
        lastMousePos = position;

        MouseMovedEvent event(offset);
        data.eventCallback(event);
    });
}
