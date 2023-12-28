#include "stdafx.h"
#include "ScreenText.h"

ScreenText::ScreenText(const char *text, SDL_Renderer *renderer, int char_width, int char_height, SDL_Color font_color, int scale, SDL_Point position)
    : text(text), charWidth(char_width), charHeight(char_height), scale(scale), position(position)
{
   this->charset = TextureManager::loadTexture(CHARSET_FILE_PATH, renderer);
   SDL_SetTextureColorMod(this->charset, font_color.r, font_color.g, font_color.b);
}

ScreenText::~ScreenText()
{
    SDL_DestroyTexture(this->charset);
}

void ScreenText::centerText()
{
    this->position = {
        (SCREEN_WIDTH_MIDDLE - this->getWidth()),
        (SCREEN_HEIGHT_MIDDLE - this->getHeight())
    };
}

void ScreenText::setPosition(SDL_Point new_position)
{
    this->position = new_position;
}

void ScreenText::updateText(const char *new_text)
{
    this->text = _strdup(new_text);
}

void ScreenText::renderText(SDL_Renderer *renderer)
{
    int c;
    SDL_Rect src = {
        0,
        0,
        this->charWidth,
        this->charHeight
    };

    SDL_Rect dest = {
        this->position.x,
        this->position.y,
        this->charWidth * this->scale,
        this->charHeight * this->scale
    };

    for (int i = 0; text[i] != '\0'; i++)
    {
        c = this->text[i] & 255;

        src.x = (c % 16) * this->charWidth;
        src.y = (c / 16) * this->charHeight;
        dest.x = this->position.x + i * this->charWidth * this->scale;

        SDL_RenderCopy(renderer, this->charset, &src, &dest);
    }
}

void ScreenText::renderText(SDL_Renderer *renderer, int pos_x, int pos_y)
{
    int c;
    SDL_Rect src = {
        0,
        0,
        this->charWidth,
        this->charHeight
    };

    SDL_Rect dest = {
        pos_x,
        pos_y,
        this->charWidth * this->scale,
        this->charHeight * this->scale
    };

    for (int i = 0; text[i] != '\0'; i++)
    {
        c = this->text[i] & 255;

        src.x = (c % 16) * this->charWidth;
        src.y = (c / 16) * this->charHeight;
        dest.x = pos_x + i * this->charWidth * this->scale;

        SDL_RenderCopy(renderer, this->charset, &src, &dest);
    }
}
