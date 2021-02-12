#pragma once

#include <glm/glm.hpp>

class Entity
{
public:
    Entity();
    virtual ~Entity() = default;

    void update(float delta);

public:
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

protected:
    virtual void onUpdate(float delta) = 0;

protected:
    glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_acceleration = { 0.0f, 0.0f, 0.0f };
};