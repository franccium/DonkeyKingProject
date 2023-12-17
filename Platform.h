#pragma once
#include "Entity.h"
#include "TextureManager.h"

class Platform
    : public Entity
{
public:
    Platform(SDL_Renderer *renderer, float pos_x, float pos_y);
    ~Platform();

    void update(const float& dt);
    void render(SDL_Renderer* renderer);
};

