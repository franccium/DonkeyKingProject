#include "stdafx.h"
#include "Platform.h"

Platform::Platform(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(PLATFORM_SPRITE_PATH, renderer, pos_x, pos_y)
{
    //TextureManager::loadTexture(PLATFORM_SPRITE_PATH, renderer, &this->sprite);
    //puts("creatd platform");
}

Platform::~Platform()
{
}

void Platform::update(const float& dt)
{
    
}

void Platform::render(SDL_Renderer* renderer)
{
    this->renderSprite(renderer);
    //puts("rendered platform");
}
