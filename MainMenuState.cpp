#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(SDL_Renderer* renderer, Game* game)
    : ScreenState(renderer), game(game)
{
    this->initTexts();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initTexts()
{
    this->guiManager->addScreenText("Donkey King", CHARSET_CHAR_W, CHARSET_CHAR_H, MAGENTA, 4, {200, 100});
    this->guiManager->addScreenText("Press N to start a New Game", CHARSET_CHAR_W, CHARSET_CHAR_H, GREEN, 3, {200, 300});
    this->guiManager->addScreenText("Press ESC to quit", CHARSET_CHAR_W, CHARSET_CHAR_H, RED, 3, {200, 450});
    this->guiManager->addScreenText("Press S for Scores", CHARSET_CHAR_W, CHARSET_CHAR_H, YELLOW, 2, {800, 540});
    this->guiManager->addScreenText("Press L to pick a Level", CHARSET_CHAR_W, CHARSET_CHAR_H, YELLOW, 2, {800, 630});
}

void MainMenuState::updateInput()
{
    /*
    SDL_Event event;
    ScreenState *newState = NULL;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_n)
                newState = new GameState(this->renderer);
            if (event.key.keysym.sym == SDLK_s)
                newState = new ScoresState(this->renderer);
            if (event.key.keysym.sym == SDLK_l)
                newState = new LevelPickerState(this->renderer);
            break;
        default:
            break;
        };
    }

    if (newState != NULL)
        game->changeScreenState(newState);*/

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_N])
    {
        this->game->changeScreenState(new GameState(this->renderer, this->game, FIRST_LEVEL));
    }
    if(state[SDL_SCANCODE_S])
    {
        this->game->changeScreenState(new ScoresState(this->renderer));
    }
    if(state[SDL_SCANCODE_L])
    {
        this->game->changeScreenState(new LevelPickerState(this->renderer));
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateInput();
}

void MainMenuState::render(SDL_Renderer* renderer)
{
    this->guiManager->renderTexts(renderer);
}
