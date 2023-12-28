#pragma once
#include "GuiManager.h"

class ScreenState
{
protected:
    SDL_Renderer* renderer;
    GuiManager* guiManager;

public:
    ScreenState(SDL_Renderer* renderer);
    virtual ~ScreenState();
    
    virtual void updateInput() = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

