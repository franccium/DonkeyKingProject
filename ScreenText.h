#pragma once
#include "TextureManager.h"

class ScreenText
{
private:
    SDL_Texture *charset;
    int charWidth;
    int charHeight;
    const char *text;
    int scale;
    SDL_Point position;

public:
    ScreenText(const char *text, SDL_Renderer *renderer, 
    int char_width, int char_height, SDL_Color font_color, 
    int scale, SDL_Point position);
    ~ScreenText();

    const int getWidth() const { return strlen(this->text) * this->charWidth; }
    const int getHeight() const { return this->charHeight; }
    void centerText();
    void setPosition(SDL_Point new_position);
    void updateText(const char *new_text);
    void renderText(SDL_Renderer *renderer);
    void renderText(SDL_Renderer *renderer, int pos_x, int pos_y);
};

