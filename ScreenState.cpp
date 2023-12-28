#include "stdafx.h"
#include "ScreenState.h"

ScreenState::ScreenState(SDL_Renderer* renderer)
    : renderer(renderer), guiManager(new GuiManager(renderer))
{
}

ScreenState::~ScreenState()
{
    delete this->guiManager;
}
