#include "stdafx.h"
#include "BarrelSet.h"

#include "stdafx.h"
#include "Donkey.h"

#include "stdafx.h"
#include "Barrel.h"

BarrelSet::BarrelSet(SDL_Renderer* renderer, float pos_x, float pos_y)
    : Entity(BARREL_SET_SPRITE_PATH, renderer, pos_x, pos_y)
{

}

BarrelSet::~BarrelSet()
{

}

void BarrelSet::render(SDL_Renderer* renderer)
{
    this->renderSprite(renderer);

    this->drawHitbox(renderer);
}