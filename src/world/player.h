#pragma once

#include "core/event.h"
#include "entity.h"

class Player : public Entity
{
public:
    Player();

    void onUpdate(float delta) override;
    void onMouseMoved(const glm::vec2& offset);

private:
};