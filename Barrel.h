#pragma once
#include "Entity.h"

class Barrel :
    public Entity
{
private:
    SDL_FPoint velocity;
    bool isInAir;

public:
    Barrel(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Barrel();

    void move(short move_direction);
    void updatePosition(const float &dt);
    void updateGravity(const float& dt);
    void setInAir(bool isInAir);
    void stopHorizontalMovement();
    const bool getOutOfBounds();
    void update(const float &dt) override;
    void render(SDL_Renderer* renderer) override;
};

