#include "player.h"
#include "core/input.h"

Player::Player()
{
}

void Player::onUpdate(float)
{
    float yaw = glm::radians(rotation.x);
    constexpr glm::vec3 up = { 0.0f, 1.0f, 0.0f };
    glm::vec3 front = glm::normalize(glm::vec3(glm::cos(yaw), 0.0f, glm::sin(yaw)));
    glm::vec3 right = glm::cross(front, up);

    glm::vec3 force = { 0.0f, 0.0f, 0.0f };

    if (Input::isKeyPressed(GLFW_KEY_W))
        force += front;
    if (Input::isKeyPressed(GLFW_KEY_S))
        force -= front;
    if (Input::isKeyPressed(GLFW_KEY_D))
        force += right;
    if (Input::isKeyPressed(GLFW_KEY_A))
        force -= right;

    if (Input::isKeyPressed(GLFW_KEY_SPACE))
        force += up;
    if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        force -= up;

    if (glm::length(force) != 0)
        m_acceleration += glm::normalize(force);
}

void Player::onMouseMoved(const glm::vec2& offset)
{
    constexpr float sensitivity = 0.1f;
    rotation.x += offset.x * sensitivity;
    rotation.y = glm::clamp(rotation.y - offset.y * sensitivity, -89.0f, 89.0f);
}
