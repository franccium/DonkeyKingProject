#include "stdafx.h"
#include "ScoresState.h"

ScoresState::ScoresState(SDL_Renderer *renderer)
    : ScreenState(renderer)
{
    this->initTexts();
}

ScoresState::~ScoresState()
{
}

void ScoresState::loadScores()
{
    FILE* scoresFile = fopen(SCORES_FILE_PATH, "r");

    // musza byc posortowane jeszcze potem
    fclose(scoresFile);
}

void ScoresState::initTexts()
{
    this->guiManager->addScreenText("Press M to return to menu", CHARSET_CHAR_W, CHARSET_CHAR_H, YELLOW, 2, {800, 630});
}

void ScoresState::updateInput()
{

}

void ScoresState::update(const float &dt)
{
    this->updateInput();
}

void ScoresState::render(SDL_Renderer *renderer)
{
    this->guiManager->renderTexts(renderer);
}
