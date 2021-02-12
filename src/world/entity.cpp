#include "entity.h"

Entity::Entity()
{
}

void Entity::update(float delta)
{
    onUpdate(delta);
}