#pragma once
#include "Entity.h"

class BonusTrophy :
    public Entity
{
public:
    BonusTrophy(SDL_Renderer *renderer, float pos_x, float pos_y);
    ~BonusTrophy();

    void move(short move_direction);
    void updatePosition(const float &dt);
    void update(const float &dt) override;
    void render(SDL_Renderer *renderer) override;
};

