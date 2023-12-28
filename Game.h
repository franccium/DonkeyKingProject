#pragma once
class ScreenState;
class MainMenuState;
#include "MainMenuState.h"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isPlaying;

    ScreenState* screenState;
    MainMenuState* menuState;

    float dt;
    Uint32 lastTime;
    Uint32 dtDelay = 1000 / FPS_CAP;

    int lastScore;

public:
    Game();
    ~Game();

    void initWindow();

    void initScreenState();
    void switchToMenuState();
    void changeScreenState(ScreenState* new_screen_state);

    void saveScore(int score);

    void handleEvents();
    void updateDt();
    void update();
    void render();
    void runGame();
    void quitGame();
};

