#pragma once
#include "ScreenState.h"

class MainMenuState :
    public ScreenState
{
public:
    MainMenuState(SDL_Renderer* renderer);
    ~MainMenuState();

    void updateInput(const float &dt) override;
    void update(const float& dt) override;
    void render(SDL_Renderer* renderer) override;
};

