#pragma once

class ScreenState
{
protected:
    SDL_Renderer* renderer;

public:
    ScreenState(SDL_Renderer* renderer);
    virtual ~ScreenState() {};

    virtual void updateInput(const float &dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

