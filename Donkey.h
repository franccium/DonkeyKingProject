#pragma once
#include "Entity.h"

class Donkey :
    public Entity
{
private:
    float barrelCooldown = 3.f;
    float barrelTimer;

public:
    Donkey(SDL_Renderer *renderer, float pos_x, float pos_y);
    ~Donkey();

    const bool getBarrelReady(const float& dt);
    void move(short move_direction);
    void updatePosition(const float& dt);
    void update(const float& dt) override;
    void render(SDL_Renderer* renderer) override;
};

