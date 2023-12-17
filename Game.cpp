#include "stdafx.h"
#include "Game.h"

Game::Game()
    : window(NULL), renderer(NULL), isPlaying(false), screenState(NULL), dt(0.0f)
{
    this->initWindow();
    this->initScreenState();
    this->lastTime = SDL_GetTicks();
}

Game::~Game() 
{ 
}

void Game::initWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        printf("Error: at Game: SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->window, &this->renderer) != 0) {
      SDL_Quit();
      printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
      return;
    };

    SDL_SetWindowTitle(this->window, WINDOW_TITLE);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);

    this->isPlaying = true;
}

void Game::initScreenState()
{
    this->screenState = new GameState(this->renderer);
}

// handles events for quiting the game
void Game::handleEvents() 
{ 
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) 
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            this->isPlaying = false;
        break;
    case SDL_QUIT:
        this->isPlaying = false;
        break;
    default:
        break;
    };
}

void Game::updateDt()
{
    Uint32 currtime = SDL_GetTicks();
    this->dt = (currtime - lastTime) * 0.001;

    if(this->dtDelay > dt)
    {
        SDL_Delay(this->dtDelay - dt);
    }

    lastTime = currtime;
}

void Game::update() 
{
    this->updateDt();
    this->screenState->update(this->dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    this->screenState->render(this->renderer);

    // SDL_Texture* texture =
    //     TextureManager::LoadTexture(PLAYER_SPRITE_PATH, this->renderer);
    // TextureManager::renderTexture(this->renderer, texture, 20, 30);

    SDL_RenderPresent(this->renderer);
}

void Game::runGame()
{
    while(this->isPlaying)
    {
        this->handleEvents();
        this->update();
        this->render();
    }

    this->quitGame();
}

void Game::quitGame()
{
    delete this->screenState;
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

