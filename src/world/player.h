#include "entity.h"

class Player : public Entity
{
public:
    Player();

    void onUpdate(float delta) override;

private:
};