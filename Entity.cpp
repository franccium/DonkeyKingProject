#include "stdafx.h"
#include "Entity.h"

Entity::Entity(const char* file_name, SDL_Renderer* renderer, float pos_x, float pos_y)
{
    this->loadSprite(file_name, renderer);
    this->setPosition(pos_x, pos_y);
    this->updateSpritePosition();
    this->setHiboxOffset(NO_HITBOX_OFFSET);
    this->initHitbox();
}

Entity::~Entity()
{
    this->destroySprite();
}

// creates a hitbox based on the sprite's size
void Entity::initHitbox()
{/*
    this->hitbox = {
        (int)this->position.x,
        (int)this->position.y,
        this->sprite.width,
        this->sprite.height
    };*/
    this->hitbox = {
        this->position.x + this->hitboxOffset.x,
        this->position.y + this->hitboxOffset.y,
        (float)this->sprite.width - this->hitboxOffset.w,
        (float)this->sprite.height - this->hitboxOffset.h
    };
}

void Entity::setHiboxOffset(SDL_FRect offset_rect)
{
    this->hitboxOffset = offset_rect;
}

void Entity::destroySprite()
{
    if (this->sprite.texture != NULL)
    {
        SDL_DestroyTexture(this->sprite.texture);
        this->sprite.texture = NULL;
    }
}

SDL_Point Entity::getSpriteDimensions()
{
    return {this->sprite.width, this->sprite.height};
}

SDL_Rect Entity::getHitboxRectI() const
{
    SDL_Rect hitbox = {
        (int)this->positionI.x, 
        (int)this->positionI.y,
        this->sprite.width,
        this->sprite.height
    };
    
    return hitbox;
}

SDL_FRect Entity::getHitboxRect() const
{/*
    SDL_FRect hitbox = {
        this->position.x,
        this->position.y,
        this->sprite.width,
        this->sprite.height
    };*/

    return this->hitbox;
}

void Entity::updateHitboxPosition()
{
    //this->hitbox.x = (int)this->position.x + this->hitboxOffsetX;
    //this->hitbox.y = (int)this->position.y + this->hitboxOffsetY;
    this->hitbox.x = this->position.x + this->hitboxOffset.x;
    this->hitbox.y = this->position.y + this->hitboxOffset.y;
}

bool Entity::isCollidingI(const SDL_Rect& other) const
{
    //SDL_Rect hitbox = this->getHitboxRect();
    return false;
    //return SDL_HasIntersection(&this->hitbox, &other);
}

bool Entity::isColliding(const SDL_FRect& other) const
{
    //SDL_FRect hitbox = this->getHitboxRect();

    return SDL_HasIntersectionF(&this->hitbox, &other);
}

void Entity::drawHitbox(SDL_Renderer* renderer) 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, &this->hitbox);
}