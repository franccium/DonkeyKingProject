#pragma once
#include "ScreenState.h"

class LevelPickerState :
    public ScreenState
{
public:
    LevelPickerState(SDL_Renderer *renderer);
    ~LevelPickerState();

    void initTexts();

    void updateInput() override;
    void update(const float &dt) override;
    void render(SDL_Renderer *renderer) override;
};

