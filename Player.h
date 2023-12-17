#pragma once
#include "Entity.h"

class Player
    : public Entity
{
private:
    SDL_FPoint velocity;
    bool isInAir;
    bool canClimb;

public:
    Player(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Player();

    const SDL_FPoint getVelocity() const;
    void setVelocity(SDL_FPoint new_velocity);

    void move();
    void updatePosition();
    void moveLeft(const float &dt);
    void moveRight(const float &dt);
    void climb(const short climb_direction);
    void jump();
    void updateGravity(const float &dt);
    void setInAir(bool isInAir);
    void setCanClimb(bool can_climb);
    void stopHorizontalMovement();
    void updateMovementInput(SDL_Event event, const float &dt);
    void update(const float &dt) override;
    void render(SDL_Renderer* renderer) override;
};
