#include <glad/glad.h>

#include "window.h"

static void GLFWErrorCallback(int error, const char* description)
{
    CC_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

static void OpenGLMessageCallback(unsigned /*source*/, unsigned /*type*/, unsigned id,
                                  unsigned severity, int /*length*/, const char* message,
                                  const void* /*userParam*/)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_LOW: CC_LOG_INFO("OpenGL Info ({0}): {1}", id, message); return;
    case GL_DEBUG_SEVERITY_MEDIUM: CC_LOG_WARN("OpenGL Warn ({0}): {1}", id, message); return;
    case GL_DEBUG_SEVERITY_HIGH: CC_LOG_ERROR("OpenGL Error ({0}): {1}", id, message); return;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        CC_LOG_TRACE("OpenGL Trace ({0}): {1}", id, message);
        return;
    }

    CC_ASSERT_MSG(false, "Unknown severity level!");
}

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    m_data.width = width;
    m_data.height = height;
    m_data.title = title;

    CC_LOG_INFO("Creating window: {0} ({1}px by {2}px)", m_data.title, m_data.width, m_data.height);

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
        m_window = glfwCreateWindow(static_cast<int>(m_data.width), static_cast<int>(m_data.height),
                                    m_data.title.c_str(), nullptr, nullptr);
        CC_ASSERT_MSG(m_window, "Could not create window!");

        glfwMakeContextCurrent(m_window);
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

        CC_ASSERT_MSG(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5),
                      "CalbaCraft requires at least OpenGL version 4.5!");

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
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}