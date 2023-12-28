#pragma once
#include "Entity.h"
#include "AnimationPlayer.h"

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

    AnimationPlayer* animationPlayer;

    enum PlayerStates
    {
        IDLE,
        WALKING,
        JUMPING,
        CLIMBING_DOWN,
        CLIMBING_UP
    };
    PlayerStates currentState;

public:
    Player(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Player();

    const SDL_FPoint getVelocity() const;
    void setVelocity(SDL_FPoint new_velocity);

    const bool getCanClimb() const;
    const bool getIsClimbing() const;
    const bool getInAir() const;
    const PlayerStates getPlayerState() const;

    void initAnimations(SDL_Renderer *renderer);

    void updatePosition(const float &dt);
    void move(short move_direction);
    void climb(const short climb_direction);
    void jump();
    void updateGravity(const float &dt);
    void setInAir(bool isInAir);
    void setCanClimb(bool can_climb);
    void setCanClimbUp(bool can_climb_up);
    void setCanClimbDown(bool can_climb_down);
    void stopHorizontalVelocity();
    void stopVerticalVelocity();
    void updateMovementInput(const float &dt);
    void updateAnimations();
    void update(const float &dt) override;
    void render(SDL_Renderer* renderer) override;
};
