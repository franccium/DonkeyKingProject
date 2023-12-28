#pragma once
#include "Texturemanager.h"

class Entity
{
protected:
    SDL_Point positionI;
    SDL_FPoint position;
    Sprite sprite;
    SDL_FRect hitbox;

    SDL_FRect hitboxOffset;

    // int spriteWidth;
    // int spriteHeight;

    public : Entity(const char *file_name, SDL_Renderer *renderer, float pos_x, float pos_y);
    virtual ~Entity();

    //void addMovementComponent(const float termVelocity, const float acceleration); // moze dla beczek deceleration jak spadaja?
    //void addHitboxComponent(SDL_Rect& hitboxRect, float offsetX, float offsetY);   // , float width, float height
    void initHitbox();
    void setHiboxOffset(SDL_FRect offset_rect);

    inline virtual const SDL_Point& getPositionI() const { return this->positionI; };
    inline virtual const SDL_FPoint& getPosition() const { return this->position; };
    inline virtual void setPositionI(const int x, const int y)
    {
        this->positionI = {x, y};
    }
    inline virtual void setPosition(const float x, const float y) 
    {
        this->position = {x, y};
    }
    inline virtual void updateSpritePosition()
    {
        this->sprite.position.x = (int)this->position.x;
        this->sprite.position.y = (int)this->position.y;
    }

    //virtual void stopVelocity();
    //virtual void stopVelocityX();
    //virtual void stopVelocityY();
    inline void loadSprite(const char* file_name, SDL_Renderer* renderer) 
    {
        //this->sprite.texture = TextureManager::LoadTexture(file_name, renderer, &sprite);
        TextureManager::loadSprite(file_name, renderer, &this->sprite);
    }
    inline void renderSprite(SDL_Renderer* renderer) 
    { 
        TextureManager::renderTexture(renderer, &this->sprite); 
    }
    void destroySprite();

    SDL_Point getSpriteDimensions();

    void updateHitboxPosition();
    SDL_Rect getHitboxRectI() const;
    SDL_FRect getHitboxRect() const;
    bool isCollidingI(const SDL_Rect& other) const;
    bool isColliding(const SDL_FRect& other) const;
    void drawHitbox(SDL_Renderer* renderer);

    virtual void update(const float& dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

