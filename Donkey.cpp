#include "stdafx.h"
#include "Donkey.h"

#include "stdafx.h"
#include "Barrel.h"

Donkey::Donkey(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(DONKEY_SPRITE_PATH, renderer, pos_x, pos_y)
{
    
}

Donkey::~Donkey()
{
    
}

void Donkey::updatePosition(const float &dt)
{
    //this->position.x += this->velocity.x * dt;
    //this->position.y += this->velocity.y * dt;
    this->updateSpritePosition();
}

const bool Donkey::getBarrelReady()
{
    Uint32 barrelTime = SDL_GetTicks();

    if (barrelTime - this->lastBarrelTime >= this->barrelCooldown)
    {
        this->lastBarrelTime = barrelTime;
        return true;
    }

    return false;
}

void Donkey::move(short move_direction)
{
    // idzie w gore po skonczeniu levela
}

void Donkey::update(const float &dt)
{
    this->updatePosition(dt);
    this->updateHitboxPosition();
}

void Donkey::render(SDL_Renderer *renderer)
{
    this->renderSprite(renderer);

    this->drawHitbox(renderer);
}