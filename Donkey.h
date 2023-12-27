#pragma once
#include "Entity.h"

class Donkey :
    public Entity
{
private:
    Uint32 barrelCooldown = 3000;
    Uint32 lastBarrelTime = 0;

public:
    Donkey(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Donkey();

    const bool getBarrelReady();
    void move(short move_direction);
    void updatePosition(const float& dt);
    void update(const float& dt) override;
    void render(SDL_Renderer* renderer) override;
};

