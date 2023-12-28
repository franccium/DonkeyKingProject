#include "stdafx.h"
#include "GuiManager.h"

GuiManager::GuiManager(SDL_Renderer* renderer)
    : texts(NULL), textCount(0), renderer(renderer)
{
}

GuiManager::~GuiManager()
{
    for (int i = 0; i < this->textCount; i++)
        delete this->texts[i];
    
    delete[] this->texts;
}

int GuiManager::addScreenText(const char *text, int char_width, 
int char_height, SDL_Color font_color, int scale, SDL_Point position)
{
    ScreenText** temp = new ScreenText*[this->textCount + 1];
    for (int i = 0; i < this->textCount; i++)
        temp[i] = this->texts[i];

    temp[textCount] = new ScreenText(text, this->renderer, char_width, char_height, font_color, scale, position);
    if(this->texts != NULL)
        delete[] this->texts;

    texts = temp;
    this->textCount++;

    return this->textCount - 1;
}

void GuiManager::updateText(int index, const char *text)
{
    this->texts[index]->updateText(text);
}

void GuiManager::renderText(int index, SDL_Renderer* renderer, int pos_x, int pos_y)
{
    this->texts[index]->renderText(renderer, pos_x, pos_y);
}


void GuiManager::renderTexts(SDL_Renderer* renderer)
{
    for (int i = 0; i < this->textCount; i++)
        this->texts[i]->renderText(renderer);
}
