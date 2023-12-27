#include "stdafx.h"
#include "Ladder.h"

Ladder::Ladder(SDL_Renderer* renderer, float pos_x, float pos_y)
	: Entity(LADDER_SPRITE_PATH, renderer, pos_x, pos_y)
{
}

Ladder::~Ladder()
{
}

void Ladder::update(const float& dt)
{
}

void Ladder::render(SDL_Renderer* renderer)
{
	this->renderSprite(renderer);

    this->drawHitbox(renderer);
}
