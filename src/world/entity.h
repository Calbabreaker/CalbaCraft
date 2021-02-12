#pragma once

#include <glm/glm.hpp>

class Entity
{
public:
    Entity();
    virtual ~Entity() = default;

    void update(float delta);

    virtual void onUpdate(float delta) = 0;

public:
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
};