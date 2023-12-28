#pragma once
#include "ScreenState.h"

class ScoresState :
    public ScreenState
{
public:
    ScoresState(SDL_Renderer *renderer);
    ~ScoresState();

    void loadScores();
    void initTexts();

    void updateInput() override;
    void update(const float &dt) override;
    void render(SDL_Renderer *renderer) override;
};

