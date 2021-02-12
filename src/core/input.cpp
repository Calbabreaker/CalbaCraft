#include "input.h"
#include "application.h"

namespace Input {

    bool isKeyPressed(int key)
    {
        GLFWwindow* context = Application::get().getWindow().getContext();

        int state = glfwGetKey(context, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool isMouseButtonPressed(int button)
    {
        GLFWwindow* context = Application::get().getWindow().getContext();

        int state = glfwGetMouseButton(context, button);
        return state == GLFW_PRESS;
    }

    glm::vec2 getMousePosition()
    {
        GLFWwindow* context = Application::get().getWindow().getContext();

        double xPos, yPos;
        glfwGetCursorPos(context, &xPos, &yPos);
        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

} // namespace Input