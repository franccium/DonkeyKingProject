#pragma once
#include "Entity.h"

class Ladder :
    public Entity
{
public:
    Ladder(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Ladder();

    void update(const float& dt);
    void render(SDL_Renderer* renderer);
};

