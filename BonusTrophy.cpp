#include "stdafx.h"
#include "BonusTrophy.h"

BonusTrophy::BonusTrophy(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(BONUS_TROPHY_SPRITE_PATH, renderer, pos_x, pos_y)
{
}

BonusTrophy::~BonusTrophy()
{
}

void BonusTrophy::updatePosition(const float &dt)
{
    // this->position.x += this->velocity.x * dt;
    // this->position.y += this->velocity.y * dt;
    this->updateSpritePosition();
}

void BonusTrophy::move(short move_direction)
{
    // idzie w gore po skonczeniu levela
}

void BonusTrophy::update(const float &dt)
{
    // this->updatePosition(dt);
    // this->updateHitboxPosition();
}

void BonusTrophy::render(SDL_Renderer *renderer)
{
    this->renderSprite(renderer);

    this->drawHitbox(renderer);
}