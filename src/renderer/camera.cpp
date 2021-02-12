#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

void Camera::update(const Entity& entity)
{
    float yaw = glm::radians(entity.rotation.x);
    float pitch = glm::radians(entity.rotation.y);

    glm::vec3 direction;
    direction.x = glm::cos(yaw) * glm::cos(pitch);
    direction.y = glm::sin(pitch);
    direction.z = glm::sin(yaw) * glm::cos(pitch);
    glm::vec3 front = glm::normalize(direction);

    constexpr glm::vec3 up = { 0.0f, 1.0f, 0.0f };
    glm::mat4 view = glm::lookAt(entity.position, entity.position + front, up);
    m_viewProjection = getProjection() * view;
}

void Camera::setViewportSize(uint32_t width, uint32_t height)
{
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(fov, m_aspectRatio, near, far);
}