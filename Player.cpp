#include "stdafx.h"
#include "Player.h"

Player::Player(SDL_Renderer *renderer, float pos_x, float pos_y)
    : Entity(PLAYER_IDLE_SPRITE_PATH, renderer, pos_x, pos_y)
{
    this->initAnimations(renderer);
    this->sprite.width = 64;
    this->sprite.height = 64;

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

const bool Player::getInAir() const
{
    return this->isInAir;
}

const Player::PlayerStates Player::getPlayerState() const
{
    return this->currentState;
}

void Player::initAnimations(SDL_Renderer* renderer)
{
    this->animationPlayer = new AnimationPlayer(2, renderer);
    this->animationPlayer->addAnimation(0, PLAYER_IDLE_SPRITE_PATH, 0.2f, 5, 64, 64, true);
    this->animationPlayer->addAnimation(1, PLAYER_CLIMB_SPRITE_PATH, 0.2f, 2, 64, 64, true);
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

void Player::updateMovementInput(const float& dt)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A])
        this->move(MOVE_LEFT);
    else if (state[SDL_SCANCODE_D])
        this->move(MOVE_RIGHT);
    else 
        this->stopHorizontalVelocity();
    
    if (state[SDL_SCANCODE_SPACE])
        this->jump();
    /*
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
            this->climb(CLIMB_UP);
    }
    else if(this->canClimbDown)
    {
         if (state[SDL_SCANCODE_S])
            this->climb(CLIMB_DOWN);
    }

}

void Player::updateAnimations()
{
    if(this->currentState == CLIMBING_DOWN || this->currentState == CLIMBING_UP)
    {
        this->animationPlayer->playAnimation(1);
    }
    else
    {
        this->animationPlayer->playAnimation(0);
    }
    if(this->velocity.x == 0.f && this->velocity.y == 0.f)
    {
        this->animationPlayer->playAnimation(0);
    }
    if(this->velocity.x < 0.f) 
        this->animationPlayer->flipAnimation();
    else if(this->velocity.x > 0.f) 
        this->animationPlayer->removeFlip();
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

    this->canClimb = can_climb_up;
}

void Player::setCanClimbDown(bool can_climb_down)
{
    this->canClimbDown = can_climb_down;

    this->canClimb = can_climb_down;
}

void Player::stopHorizontalVelocity()
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
    this->updateMovementInput(dt);
    this->updateGravity(dt);
    
    this->updatePosition(dt);
    this->updateHitboxPosition();

    this->updateAnimations();
    this->animationPlayer->update(dt);
}

void Player::render(SDL_Renderer* renderer)
{
    //this->renderSprite(renderer);

    this->drawHitbox(renderer);

    this->animationPlayer->render(renderer, this->position.x, this->position.y);
}

