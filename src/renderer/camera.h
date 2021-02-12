#pragma once

#include "world/entity.h"

class Camera
{
public:
    Camera() = default;

    void update(const Entity& entity);
    void setViewportSize(uint32_t width, uint32_t height);

    glm::mat4 getProjection() const;
    const glm::mat4& getViewProjection() const { return m_viewProjection; }

public:
    float fov = 60.0f;
    float near = 0.01f;
    float far = 1000.0f;

private:
    glm::vec3 m_up = { 0.0f, 1.0f, 0.0f };
    glm::mat4 m_viewProjection = glm::mat4(1.0f);

    float m_aspectRatio = 0.0f;
};