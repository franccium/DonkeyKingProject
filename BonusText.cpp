#include "stdafx.h"
#include "BonusText.h"

BonusText::BonusText(const char *text, float lifetime, 
        SDL_Renderer *renderer, int char_width, 
        int char_height, SDL_Color font_color, 
        int scale, SDL_Point position)
    : ScreenText(text, renderer, char_width, char_height, font_color, scale, position), lifetime(lifetime)
{
    
}

BonusText::~BonusText()
{
    
}

const bool BonusText::getLifetimeExpired(const float& dt)
{
    this->lifetime -= dt;

    if(this->lifetime <= 0)
        return true;
    else
        return false;
}
