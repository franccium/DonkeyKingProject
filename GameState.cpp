#include "stdafx.h"
#include "GameState.h"

GameState::GameState(SDL_Renderer* renderer)
    : ScreenState(renderer), player(NULL), barrels(NULL)
{
    this->initLevel();
}

GameState::~GameState()
{
    delete this->player;

    for (int i = 0; i < this->platformCount; i++)
    {
        delete this->platforms[i];
    }
    free(this->platforms);

    for (int i = 0; i < barrelCount; i++)
    {
        delete this->barrels[i];
    }
    delete[] this->barrels;
}

void GameState::initPlayer()
{
    this->player = new Player(this->renderer, 250.f, 500.f);
}

void GameState::initLevel()
{
    this->initPlatforms();
    this->initLadders();
    this->initDonkey();
    this->initBarrels();
    this->initPlayer();
}

void GameState::initPlatforms()
{
    this->platformCount = 8;
    this->platforms = (Platform**)malloc(sizeof(Platform*) * this->platformCount);
    this->platforms[0] = new Platform(this->renderer, 150.f, 600.f);
    int platformWidth = (float)this->platforms[0]->getSpriteDimensions().x;
    int platformHeight = (float)this->platforms[0]->getSpriteDimensions().y;

    this->platforms[1] = new Platform(this->renderer, 400.f, 600.f - 128.f * 1);
    this->platforms[2] = new Platform(this->renderer, 200.f, 600.f - 128.f * 2);
    this->platforms[3] = new Platform(this->renderer, 350.f, 600.f - 128.f * 3);

    this->platforms[4] = new Platform(this->renderer, 150.f + platformWidth, 600.f);
    this->platforms[5] = new Platform(this->renderer, 400.f - platformWidth, 600.f - 128.f * 1);
    this->platforms[6] = new Platform(this->renderer, 200.f + platformWidth, 600.f - 128.f * 2);
    this->platforms[7] = new Platform(this->renderer, 350.f - platformWidth, 600.f - 128.f * 3);
}

void GameState::initLadders()
{
    this->ladderCount = 4;
    this->ladders = (Ladder**)malloc(sizeof(Ladder*) * this->ladderCount);
    this->ladders[0] = new Ladder(this->renderer, 400.f - 48.f, 600.f - 128.f);
    this->ladders[1] = new Ladder(this->renderer, 400.f + 48.f, 600.f - 128.f * 2);
    this->ladders[2] = new Ladder(this->renderer, 248.f + 48.f, 600.f - 128.f * 3);
    this->ladders[3] = new Ladder(this->renderer, 500.f - 48.f, 600.f - 128.f * 4);
}

void GameState::initDonkey()
{
    this->donkey = new Donkey(this->renderer, 500.f, 50.f);
}

void GameState::initBarrels()
{
    this->barrelCount = 0;
    this->barrels = new Barrel*[MAX_BARREL_COUNT];
}

void GameState::renderPlatforms(SDL_Renderer* renderer)
{
    for (int i = 0; i < this->platformCount; i++)
    {
        this->platforms[i]->render(renderer);
    }
}

void GameState::renderLadders(SDL_Renderer* renderer)
{
    for (int i = 0; i < this->ladderCount; i++)
    {
        this->ladders[i]->render(renderer);
    }
}

void GameState::renderBarrels(SDL_Renderer *renderer)
{
    for (int i = 0; i < this->barrelCount; i++)
    {
        this->barrels[i]->render(renderer);
    }
}

void GameState::spawnBarrels()
{
    if(this->donkey->getBarrelReady())
    {
        if(this->barrelCount < MAX_BARREL_COUNT)
        {
            this->barrels[this->barrelCount] = new Barrel(
                this->renderer, 
                this->donkey->getPosition().x, 
                this->donkey->getPosition().y
            );
            this->barrelCount++;
        }
    }
}

void GameState::deleteBarrel(int barrel_index)
{
    delete this->barrels[barrel_index];
    
    for (int i = barrel_index; i < this->barrelCount - 1; i++)
    {
        this->barrels[i] = this->barrels[i + 1];
    }

    this->barrelCount--;
}

void GameState::updateBarrels(const float& dt)
{
    for (int i = 0; i < this->barrelCount; i++)
    {
        this->barrels[i]->update(dt);

        if(this->barrels[i]->getOutOfBounds())
        {
            this->deleteBarrel(i);
            i--;
        }
    }
}

void GameState::renderLevel(SDL_Renderer* renderer)
{
    this->renderPlatforms(renderer);
    this->renderLadders(renderer);
    this->renderBarrels(renderer);
}

void GameState::updateCollision(const float& dt)
{
    //SDL_FPoint calculatedVelocity = this->player->getVelocity();
    int ladderCollisionCount = 0;

    /*
    SDL_FRect futurePosition = {
        this->player->getPosition().x + this->player->getVelocity().x * dt,
        this->player->getPosition().y + this->player->getVelocity().y * dt,
        this->player->getHitboxRect().w,
        this->player->getHitboxRect().h};*/

    for(int i = 0; i < this->platformCount; i++)
    {
        
        if (this->player->isColliding(this->platforms[i]->getHitboxRect()))
        {
            if (this->player->getHitboxRect().y < this->platforms[i]->getHitboxRect().y
            && !this->player->getIsClimbing()) // collision from above the platform
            {
                this->player->setPosition(
                    this->player->getPosition().x, 
                    this->platforms[i]->getHitboxRect().y - this->player->getHitboxRect().h);
                this->player->setInAir(false);
                puts("colliding above");
            } 
            else if(this->player->getHitboxRect().y > this->platforms[i]->getHitboxRect().y 
            && !this->player->getCanClimb()) // collision from below the platform
            {
                this->player->setPosition(
                    this->player->getPosition().x,
                    this->platforms[i]->getHitboxRect().y + this->platforms[i]->getHitboxRect().h);
                this->player->stopVerticalVelocity();
                puts("colliding below");
            }/*
            if (this->player->getHitboxRect().x < this->platforms[i]->getHitboxRect().x 
            && this->player->getHitboxRect().y < this->platforms[i]->getHitboxRect().y) // collision from left side
            {
                this->player->setPosition(
                    this->player->getPosition().x - this->player->getHitboxRect().w,
                    this->player->getPosition().y);
                this->player->setInAir(false);
            }
            else if (this->player->getHitboxRect().y > this->platforms[i]->getHitboxRect().y 
            && this->player->getHitboxRect().y < this->platforms[i]->getHitboxRect().y) // collision from right side
            {
                this->player->setPosition(
                    this->player->getPosition().x + this->player->getHitboxRect().w,
                    this->player->getPosition().y);
            }*/
        }

        for (int i = 0; i < barrelCount; i++)
        {
            if (this->barrels[i]->isColliding(this->platforms[i]->getHitboxRect()))
            {
                this->barrels[i]->setPosition(
                    this->barrels[i]->getPosition().x,
                    this->platforms[i]->getHitboxRect().y - this->barrels[i]->getHitboxRect().h);
                this->barrels[i]->setInAir(false);
            }
        }
       /*
        if (this->player->isColliding(this->platforms[i]->getHitboxRect()))
        {
            // Calculate the overlap between the player and the platform
            float overlapX = this->player->getHitboxRect().w + this->platforms[i]->getHitboxRect().w - SDL_fabsf(this->player->getPosition().x - this->platforms[i]->getPosition().x);
            float overlapY = this->player->getHitboxRect().h + this->platforms[i]->getHitboxRect().h - SDL_fabsf(this->player->getPosition().y - this->platforms[i]->getPosition().y);

            // Check the direction of the player's movement
            bool movingHorizontally = SDL_fabsf(this->player->getVelocity().x) > SDL_fabsf(this->player->getVelocity().y);

            // If the player is moving more horizontally than vertically, or if the overlap is smaller on the x-axis
            if (movingHorizontally || overlapX < overlapY)
            {
                // Determine if the player is to the left or right of the platform
                bool isLeft = this->player->getPosition().x < this->platforms[i]->getPosition().x;

                // Move the player out of the platform horizontally
                if (isLeft)
                {
                    // If the player is to the left of the platform, move them just to the left of it
                    this->player->setPosition(
                        this->platforms[i]->getHitboxRect().x - this->player->getHitboxRect().w,
                        this->player->getPosition().y);
                }
                else
                {
                    // If the player is to the right of the platform, move them just to the right of it
                    this->player->setPosition(
                        this->platforms[i]->getHitboxRect().x + this->platforms[i]->getHitboxRect().w,
                        this->player->getPosition().y);
                }
                calculatedVelocity.x = 0;
            }
            // If the player is moving more vertically than horizontally, or if the overlap is smaller on the y-axis
            else
            {
                bool isAbove = this->player->getPosition().y < this->platforms[i]->getPosition().y;

                // Move the player out of the platform vertically
                if (isAbove)
                {
                    // If the player is above the platform, move them just above it
                    this->player->setPosition(
                        this->player->getPosition().x,
                        this->platforms[i]->getHitboxRect().y - this->player->getHitboxRect().h);
                }
                calculatedVelocity.y = 0;
                this->player->setInAir(false);
            }
        }*/
        SDL_FRect playerHitbox = this->player->getHitboxRect();
        SDL_FRect platformHitbox = this->platforms[i]->getHitboxRect();

        // Calculate the player's bottom edge and the platform's top edge
        int playerBottom = playerHitbox.y + playerHitbox.h;
        int platformTop = platformHitbox.y;

        // Check if the player's bottom edge is within a certain range of the platform's top edge
        if (playerBottom <= platformTop && playerBottom >= platformTop - 2.f)
        {
            this->player->setCanClimbUp(true);
            puts("can climb up");
        } 
        else
        {
            this->player->setCanClimbUp(false);
            puts("can't climb up");
        }
        if(playerBottom >= platformTop && playerBottom >= platformTop - 2.f)
        {
            this->player->setCanClimbDown(true);
            puts("can climb down");
        } 
        else 
        {
            this->player->setCanClimbDown(false);
            puts("can't climb down");
        }
    

    for (int i = 0; i < this->ladderCount; i++)
    {
        if (this->player->isColliding(this->ladders[i]->getHitboxRect()))
        {
            ladderCollisionCount++;
            this->player->setCanClimb(true);
        }
    }

    if(ladderCollisionCount == 0)
    {
        this->player->setCanClimb(false);
    }

    }

    for (int i = 0; i < barrelCount; i ++)
    {
        if(this->player->isColliding(this->barrels[i]->getHitboxRect()))
        {
            puts("colliding with barrel");
        }
    }
}

void GameState::updateInput(const float& dt)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_m)
            // return to menu
        break;
    default:
        break;
    };
    
    this->player->updateMovementInput(event, dt);
}

void GameState::update(const float& dt) 
{ 
    this->updateInput(dt);

    this->player->update(dt);
    this->spawnBarrels();
    this->donkey->update(dt);
    this->updateBarrels(dt);
    this->updateCollision(dt);
}

void GameState::render(SDL_Renderer* renderer) 
{
    this->renderLevel(renderer);

    this->player->render(renderer);
    this->donkey->render(renderer);
    this->renderBarrels(renderer);
}
