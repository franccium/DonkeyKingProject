#pragma once
#include "Entity.h"

class Barrel :
    public Entity
{
private:
    SDL_FPoint velocity;
    bool isInAir;
    bool bonusPointsAvailable;

public:
    Barrel(SDL_Renderer* renderer, float pos_x, float pos_y);
    ~Barrel();

    void move(short move_direction);
    void updatePosition(const float &dt);
    void updateGravity(const float& dt);
    void setInAir(bool isInAir);
    const bool getInAir() const;
    void stopHorizontalMovement();
    void swapDirection();
    void stopVerticalVelocity();
    const bool getOutOfBounds();
    const bool getBonusPointsAvailable() const;
    void setBonusPointsAvailable(bool bonus_points_available);
    void update(const float &dt) override;
    void render(SDL_Renderer* renderer) override;
};

