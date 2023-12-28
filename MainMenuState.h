#pragma once
#include "ScreenState.h"
#include "Game.h"
#include "GameState.h"
#include "ScoresState.h"
#include "LevelPickerState.h"

class Game;

class MainMenuState :
    public ScreenState
{
private:
    Game *game;

public:
    MainMenuState(SDL_Renderer *renderer, Game* game);
    ~MainMenuState();

    void initTexts();

    void updateInput() override;
    void update(const float &dt) override;
    void render(SDL_Renderer *renderer) override;
};