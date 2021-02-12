#include "entity.h"

Entity::Entity()
{
}

void Entity::update(float delta)
{
    onUpdate(delta);

    m_velocity += m_acceleration;
    m_acceleration = { 0.0f, 0.0f, 0.0f };

    position += m_velocity * delta;
    m_velocity *= 0.5f;
}