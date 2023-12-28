#pragma once
#include "ScreenState.h"
#include "Game.h"
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "Donkey.h"
#include "BarrelSet.h"
#include "Cat.h"
#include "BonusTrophy.h"
#include "BonusText.h"

class Game;
class GameState :
    public ScreenState
{
private:
    Game *game;

    Player* player;

    Platform** platforms;
    int platformCount;
    Ladder** ladders;
    int ladderCount;

    Donkey* donkey;
    BarrelSet* barrelSet;
    Barrel** barrels;
    int barrelCount;
    int maxBarrels;

    Cat *cat;
    BonusTrophy *bonusTrophy;

    int currentLevel;
    char levelText[10];

    double timer;

    Sprite heart;
    int heartCount;
    bool lostLife;
    bool lostGame;
    ScreenText* continueText;
    ScreenText* saveScoreText;

    int score;
    int timerTxt;
    int scoreTxt;
    int levelTxt;

    BonusText** bonusTexts;
    int maxBonusTexts;
    int bonusTextCount;
    char barrelBonusPoints[4];
    char trophyBonusPoints[4];

public:
    GameState(SDL_Renderer *renderer, Game* game, int level_number);
    ~GameState();

    void initPlayer(FILE *level_file);
    void initPlatforms(FILE *level_file);
    void initLadders(FILE *level_file);
    void initDonkey(FILE *level_file);
    void initBarrels(FILE *level_file);
    void initCat(FILE *level_file);
    void initBonusTrophy(FILE *level_file);
    void initLevel(int level_number);

    void renderPlatforms(SDL_Renderer* renderer);
    void renderLadders(SDL_Renderer* renderer);
    void renderLevel(SDL_Renderer* renderer);
    void renderBarrels(SDL_Renderer* renderer);

    void spawnBarrels(const float &dt);
    void deleteBarrel(int barrel_index);
    void updateBarrels(const float& dt);

    void changeLevel(int level_number);

    void initGui();
    void updateGUI(const float& dt);
    void renderGUI(SDL_Renderer* renderer);
    void initTexts();
    void updateTimerText(const float& dt);
    void updateScoreText();
    void initBonusPointsText();
    void createBonusText(int index, const char *text, float lifetime);
    void addBonusPointsText(const char* text, float lifetime);
    void addBonusPoints(int points);
    void updateBonusPoints(const float& dt);
    void deleteBonusPointsText(int index);
    void renderBonusPoints(SDL_Renderer *renderer);
    void updateLevelText();

    void initLivesCounter();
    void renderLivesCounter(SDL_Renderer* renderer);
    void initContinueText();
    void renderContinueText(SDL_Renderer *renderer);
    void initSaveScoreText();
    void renderSaveScoreText(SDL_Renderer *renderer);

    void nextLevel();
    void gameOver();

    void updateCollision(const float &dt);
    void updateInput() override;
    void update(const float& dt) override;
    void render(SDL_Renderer* renderer) override;
};

