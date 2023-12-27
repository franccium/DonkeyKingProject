#include "stdafx.h"
#include "Barrel.h"

Barrel::Barrel(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(BARREL_SPRITE_PATH, renderer, pos_x, pos_y)
{
    this->velocity = {0.f, 0.f};
    this->isInAir = true;
}

Barrel::~Barrel()
{
}

void Barrel::updatePosition(const float &dt)
{
    this->position.x += this->velocity.x * dt;
    this->position.y += this->velocity.y * dt;
    this->updateSpritePosition();
    // char buffer[100];
    // sprintf_s(buffer, "pos: %f", position.x);
    // puts(buffer);
}

void Barrel::move(short move_direction)
{
    this->velocity.x = move_direction * BARREL_HORIZONTAL_SPEED;
    // char buffer[100];
    // sprintf_s(buffer, "vel: %f", velocity.x);
    // puts(buffer);
}

void Barrel::updateGravity(const float &dt)
{
    if (this->isInAir)
    {
        this->velocity.y += BARREL_GRAVITY * dt;
    }
}

void Barrel::setInAir(bool is_in_air)
{
    this->isInAir = is_in_air;
}

void Barrel::stopHorizontalMovement()
{
    this->velocity.x = 0;
}

const bool Barrel::getOutOfBounds()
{
    if(this->position.y > SCREEN_HEIGHT ||
        this->position.x > SCREEN_WIDTH ||
        this->position.x < 0.f ||
        this->position.y < 0.f)
    {
        return true;
    }

    return false;
}

void Barrel::update(const float &dt)
{
    this->updateGravity(dt);

    this->updatePosition(dt);
    this->updateHitboxPosition();
}

void Barrel::render(SDL_Renderer *renderer)
{
    this->renderSprite(renderer);

    this->drawHitbox(renderer);
}
