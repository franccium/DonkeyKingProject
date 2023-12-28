#pragma once
#include "Entity.h"

class BarrelSet :
    public Entity
{
public:
    BarrelSet(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~BarrelSet();
    void update(const float& dt) override {};
    void render(SDL_Renderer* renderer) override;
};

