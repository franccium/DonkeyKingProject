#include "stdafx.h"
#include "Cat.h"

Cat::Cat(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(CAT_SPRITE_PATH, renderer, pos_x, pos_y)
{
}

Cat::~Cat()
{
}

void Cat::updatePosition(const float &dt)
{
    // this->position.x += this->velocity.x * dt;
    // this->position.y += this->velocity.y * dt;
    this->updateSpritePosition();
}

void Cat::move(short move_direction)
{
    // idzie w gore po skonczeniu levela
}


void Cat::update(const float &dt)
{
    //this->updatePosition(dt);
    //this->updateHitboxPosition();
}


void Cat::render(SDL_Renderer *renderer)
{
    this->renderSprite(renderer);

    this->drawHitbox(renderer);
}