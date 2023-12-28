#pragma once
#include "ScreenText.h"

class BonusText :
    public ScreenText
{
private:
    float lifetime;

public:
    BonusText(const char *text, float lifetime, 
        SDL_Renderer *renderer, int char_width, 
        int char_height, SDL_Color font_color, 
        int scale, SDL_Point position);
    ~BonusText();

    const bool getLifetimeExpired(const float &dt);
};

