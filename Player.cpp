#include "stdafx.h"
#include "Player.h"

Player::Player(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(PLAYER_SPRITE_PATH, renderer, pos_x, pos_y)
{
    this->velocity = {0.f, 0.f};
    this->isInAir = true;
    this->canClimb = false;
}

Player::~Player() 
{
}

const SDL_FPoint Player::getVelocity() const
{
    return this->velocity;
}

void Player::setVelocity(SDL_FPoint new_velocity)
{
    this->velocity = new_velocity;
}

void Player::move()
{
    
}

void Player::updatePosition()
{
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
    this->updateSpritePosition();
    //char buffer[100];
    //sprintf_s(buffer, "pos: %f", position.x);
    //puts(buffer);
}

void Player::updateMovementInput(SDL_Event event, const float& dt)
{
    /*if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            this->moveLeft(dt);
            break;
        case SDLK_d:
            this->moveRight(dt);
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            if (velocity.x < 0)
                velocity.x = 0;
            break;
        case SDLK_d:
            if (velocity.x > 0)
                velocity.x = 0;
            break;
        }
    }*/

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A])
    {
        this->moveLeft(dt);
    }
    else if (state[SDL_SCANCODE_D])
    {
        this->moveRight(dt);
    }
    else 
    {
        this->stopHorizontalMovement();
    }
    if (state[SDL_SCANCODE_SPACE])
    {
        this->jump();
    }
    if(this->canClimb)
    {
        if (state[SDL_SCANCODE_W])
        {
            this->climb(CLIMB_UP);
        }
        else if (state[SDL_SCANCODE_S])
        {
            this->climb(CLIMB_DOWN);
        }
        else 
        {
            this->climb(CLIMB_NONE);
        }
    }
}

void Player::moveLeft(const float &dt)
{
    this->velocity.x = -PLAYER_HORIZONTAL_SPEED * dt;
    //char buffer[100];
    //sprintf_s(buffer, "vel: %f", velocity.x);
    //puts(buffer);
}

void Player::moveRight(const float &dt)
{
    this->velocity.x = PLAYER_HORIZONTAL_SPEED * dt;
    //char buffer[100];
    //sprintf_s(buffer, "vel: %f", velocity.x);
    //puts(buffer);
}

void Player::climb(const short climb_direction)
{
    this->velocity.y = climb_direction * PLAYER_CLIMB_SPEED;
    this->isInAir = true;
}

void Player::jump()
{
    if(!this->isInAir)
    {
        this->velocity.y = PLAYER_JUMP_FORCE;
        this->isInAir = true;
    }
}

void Player::updateGravity(const float& dt)
{
    if(this->isInAir)
    {
        this->velocity.y += PLAYER_GRAVITY * dt;
    }
}

void Player::setInAir(bool is_in_air)
{
    this->isInAir = is_in_air;
}

void Player::setCanClimb(bool can_climb)
{
    this->canClimb = can_climb;
}

void Player::stopHorizontalMovement()
{
    this->velocity.x = 0;
}

void updateAnimations()
{
    /*if(this->velocity.x < 0)
    {
        this->animationState = AnimationState::MOVING_LEFT;
    }
    else if(this->velocity.x > 0)
    {
        this->animationState = AnimationState::MOVING_RIGHT;
    }
    else
    {
        this->animationState = AnimationState::IDLE;
    }*/
}

void Player::update(const float& dt) 
{
    this->updateGravity(dt);

    this->updatePosition();
    this->updateHitboxPosition();
}

void Player::render(SDL_Renderer* renderer)
{
    this->renderSprite(renderer);
}

