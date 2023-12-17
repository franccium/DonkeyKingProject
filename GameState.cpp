#include "stdafx.h"
#include "GameState.h"

GameState::GameState(SDL_Renderer* renderer)
    : ScreenState(renderer), player(NULL)
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
}

void GameState::initPlayer()
{
    this->player = new Player(this->renderer, 200.f, 200.f);
}

void GameState::initLevel()
{
    this->initPlatforms();
    this->initLadders();
    this->initPlayer();
}

void GameState::initPlatforms()
{
    this->platformCount = 2;
    this->platforms = (Platform**)malloc(sizeof(Platform*) * this->platformCount);
    this->platforms[0] = new Platform(this->renderer, 150.f, 300.f);
    this->platforms[1] = new Platform(this->renderer, 400.f, 340.f);
}

void GameState::initLadders()
{
    this->ladderCount = 2;
    this->ladders = (Ladder**)malloc(sizeof(Ladder*) * this->ladderCount);
    this->ladders[0] = new Ladder(this->renderer, 180.f, 300.f - 128.f);
    this->ladders[1] = new Ladder(this->renderer, 450.f, 340.f - 128.f);
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

void GameState::renderLevel(SDL_Renderer* renderer)
{
    this->renderPlatforms(renderer);
    this->renderLadders(renderer);
}

void GameState::updateCollision()
{
    SDL_FPoint calculatedVelocity = this->player->getVelocity();
    int ladderCollisionCount = 0;

    for(int i = 0; i < this->platformCount; i++)
    {
        
        if (this->player->isColliding(this->platforms[i]->getHitboxRect()))
        {
            //this->player->stopMovementY();
            this->player->setPosition(
                this->player->getPosition().x, 
                this->platforms[i]->getHitboxRect().y - this->player->getHitboxRect().h);
            this->player->setInAir(false);
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
    this->player->setVelocity(calculatedVelocity);
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
    this->updateCollision();
}

void GameState::render(SDL_Renderer* renderer) 
{
    this->renderLevel(renderer);

    this->player->render(renderer);
}
