#include "stdafx.h"
#include "LevelPickerState.h"

LevelPickerState::LevelPickerState(SDL_Renderer *renderer)
    : ScreenState(renderer)
{
    this->initTexts();
}

LevelPickerState::~LevelPickerState()
{
}

void LevelPickerState::initTexts()
{
    this->guiManager->addScreenText("Press M to return to menu", CHARSET_CHAR_W, CHARSET_CHAR_H, YELLOW, 2, {800, 630});
}

void LevelPickerState::updateInput()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_1])
    {
        
    }
}

void LevelPickerState::update(const float &dt)
{
    this->updateInput();
}

void LevelPickerState::render(SDL_Renderer *renderer)
{
    this->guiManager->renderTexts(renderer);
}
