#include "stdafx.h"
#include "Player.h"

Player::Player(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(PLAYER_SPRITE_PATH, renderer, pos_x, pos_y)
{
    this->velocity = {0.f, 0.f};
    this->isInAir = true;
    this->canClimb = false;
    this->isClimbing = false;
    this->canClimbUp = false;
    this->canClimbDown = false;
    this->currentState = IDLE;
    this->setHiboxOffset(PLAYER_HITBOX_OFFSET);
    this->initHitbox();
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

const bool Player::getCanClimb() const
{
    return this->canClimb;
}

const bool Player::getIsClimbing() const
{
    return this->isClimbing;
}

const PlayerStates Player::getPlayerState() const
{
    return this->currentState;
}

bool Player::isFutureColliding(const SDL_FRect& future_hitbox, const SDL_FRect& obstacle_hitbox)
{
    return SDL_HasIntersectionF(&future_hitbox, &obstacle_hitbox);
}

void Player::updatePosition(const float &dt)
{
    this->position.x += this->velocity.x * dt;
    this->position.y += this->velocity.y * dt;
    //char buffer[100];
    //sprintf_s(buffer, "velY: %f", this->velocity.y);
    //puts(buffer);
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
        this->move(MOVE_LEFT);
    }
    else if (state[SDL_SCANCODE_D])
    {
        this->move(MOVE_RIGHT);
    }
    else 
    {
        this->stopHorizontalMovement();
    }
    if (state[SDL_SCANCODE_SPACE])
    {
        this->jump();
    }/*
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
    */
   if(this->canClimbUp)
   {
        if (state[SDL_SCANCODE_W])
        {
            this->climb(CLIMB_UP);
        }
    }
    else if(this->canClimbDown)
    {
         if (state[SDL_SCANCODE_S])
         {
              this->climb(CLIMB_DOWN);
         }
    }

}

void Player::move(short move_direction)
{
    this->velocity.x = move_direction * PLAYER_HORIZONTAL_SPEED;
    //char buffer[100];
    //sprintf_s(buffer, "vel: %f", velocity.x);
    //puts(buffer);
}

void Player::climb(const short climb_direction)
{
    this->velocity.y = climb_direction * PLAYER_CLIMB_SPEED;
    this->isClimbing = true;
    if(!this->isInAir) 
        this->isInAir = true;

    if(climb_direction == CLIMB_DOWN)
    {
        this->currentState = CLIMBING_DOWN;
    }
    else if(climb_direction == CLIMB_UP)
    {
        this->currentState = CLIMBING_UP;
    }
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
        this->velocity.y += PLAYER_GRAVITY * dt;
    else
        this->velocity.y = 0.f;
}

void Player::setInAir(bool is_in_air)
{
    this->isInAir = is_in_air;
}

void Player::setCanClimb(bool can_climb)
{
    this->canClimb = can_climb;
    if(!can_climb)
        this->isClimbing = false;
}

void Player::setCanClimbUp(bool can_climb_up)
{
    this->canClimbUp = can_climb_up;
}

void Player::setCanClimbDown(bool can_climb_up)
{
    this->canClimbUp = can_climb_up;
}

void Player::stopHorizontalMovement()
{
    this->velocity.x = 0.f;
}

void Player::stopVerticalVelocity()
{
    this->velocity.y = 0.f;

    //char buffer[100];
    //sprintf_s(buffer, "modified: %f", this->velocity.y);
    //puts(buffer);
}

void Player::update(const float& dt) 
{
    this->updateGravity(dt);
    
    this->updatePosition(dt);
    this->updateHitboxPosition();
}

void Player::render(SDL_Renderer* renderer)
{
    this->renderSprite(renderer);

    this->drawHitbox(renderer);
}

