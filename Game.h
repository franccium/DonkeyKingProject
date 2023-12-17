#pragma once
#include "MainMenuState.h"
#include "GameState.h"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isPlaying;

    ScreenState* screenState;

    float dt;
    Uint32 lastTime;
    Uint32 dtDelay = 1000 / FPS_CAP;

  public:
    Game();
    ~Game();

    void initWindow();
    void initScreenState();
    void handleEvents();
    void updateDt();
    void update();
    void render();
    void runGame();
    void quitGame();
};

