#pragma once
#include "Entity.h"

class Cat :
    public Entity
{
public:
    Cat(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Cat();

    void move(short move_direction);
    void updatePosition(const float &dt);
    void update(const float &dt) override;
    void render(SDL_Renderer *renderer) override;
};