#pragma once
#include "Entity.h"

class Player
    : public Entity
{
private:
    SDL_FPoint velocity;
    bool isInAir;
    bool canClimb;
    bool isClimbing;

    bool canClimbUp;
    bool canClimbDown;

    PlayerStates currentState;

public:
    Player(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Player();

    const SDL_FPoint getVelocity() const;
    void setVelocity(SDL_FPoint new_velocity);

    const bool getCanClimb() const;
    const bool getIsClimbing() const;
    const PlayerStates getPlayerState() const;

    bool isFutureColliding(const SDL_FRect& future_hitbox, const SDL_FRect& obstacle_hitbox);

    void updatePosition(const float &dt);
    void move(short move_direction);
    void climb(const short climb_direction);
    void jump();
    void updateGravity(const float &dt);
    void setInAir(bool isInAir);
    void setCanClimb(bool can_climb);
    void setCanClimbUp(bool can_climb_up);
    void setCanClimbDown(bool can_climb_down);
    void stopHorizontalMovement();
    void stopVerticalVelocity();
    void updateMovementInput(SDL_Event event, const float &dt);
    void update(const float &dt) override;
    void render(SDL_Renderer* renderer) override;
};
