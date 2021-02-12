#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Input {

    bool isKeyPressed(int key);
    bool isMouseButtonPressed(int button);
    glm::vec2 getMousePosition();

} // namespace Input