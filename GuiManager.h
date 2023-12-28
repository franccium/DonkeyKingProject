#pragma once
#include "ScreenText.h"

class GuiManager
{
private:
    ScreenText** texts;
    int textCount;
    SDL_Renderer* renderer;

public:
	GuiManager(SDL_Renderer* renderer);
    ~GuiManager();

    int addScreenText(const char *text, int char_width, 
    int char_height, SDL_Color font_color, 
    int scale, SDL_Point position);
    void updateText(int index, const char *text);

    void renderText(int index, SDL_Renderer* renderer, int pos_x, int pos_y);
    void renderTexts(SDL_Renderer* renderer);
};

