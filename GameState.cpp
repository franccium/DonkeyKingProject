#include "stdafx.h"
#include "GameState.h"

GameState::GameState(SDL_Renderer *renderer, Game* game, int level_number)
    : ScreenState(renderer), game(game), player(NULL), barrels(NULL), cat(NULL), 
    bonusTrophy(NULL), timer(0.f), currentLevel(level_number), heartCount(INITIAL_PLAYER_LIVES), 
    lostLife(false), score(0), maxBonusTexts(10), bonusTextCount(0), lostGame(false)
{
    this->initLevel(this->currentLevel);
    this->initGui();
}

GameState::~GameState()
{
    delete this->player;

    for (int i = 0; i < this->platformCount; i++)
    {
        delete this->platforms[i];
    }
    free(this->platforms);

    for (int i = 0; i < barrelCount; i++)
    {
        delete this->barrels[i];
    }
    delete[] this->barrels;

    for (int i = 0; i < this->bonusTextCount; i++)
    {
        delete this->bonusTexts[i];
    }
    delete[] this->bonusTexts;

    if(this->bonusTrophy != NULL)
        delete this->bonusTrophy;
}

void GameState::initPlayer(FILE *level_file)
{
    float x, y;
    fscanf(level_file, "PLAYER: %f %f\n", &x, &y);
    this->player = new Player(this->renderer, x, y);
}

void GameState::initPlatforms(FILE* level_file)
{
    fscanf(level_file, "PLATFORMS: %d\n", &this->platformCount);
    this->platforms = (Platform**)malloc(sizeof(Platform*) * this->platformCount);
    float x, y;
    for (int i = 0; i < this->platformCount; i++)
    {
        fscanf(level_file, "%f %f\n", &x, &y);
        this->platforms[i] = new Platform(this->renderer, x, y);
    }
}

void GameState::initLadders(FILE *level_file)
{
    fscanf(level_file, "LADDERS: %d\n", &this->ladderCount);
    this->ladders = (Ladder **)malloc(sizeof(Ladder *) * this->ladderCount);
    float x, y;
    for (int i = 0; i < this->ladderCount; i++)
    {
        fscanf(level_file, "%f %f\n", &x, &y);
        this->ladders[i] = new Ladder(this->renderer, x, y);
    }
}

void GameState::initDonkey(FILE *level_file)
{
    float x, y;
    fscanf(level_file, "DONKEY: %f %f\n", &x, &y);
    this->donkey = new Donkey(this->renderer, x, y);

    fscanf(level_file, "BARRELSET: %f %f\n", &x, &y);
    this->barrelSet = new BarrelSet(this->renderer, x, y);
}

void GameState::initBarrels(FILE *level_file)
{
    fscanf(level_file, "BARRELS: %d\n", &this->maxBarrels);
    this->barrelCount = 0;
    this->barrels = new Barrel*[this->maxBarrels];
}

void GameState::initCat(FILE *level_file)
{
    float x, y;
    fscanf(level_file, "CAT: %f %f\n", &x, &y);
    this->cat = new Cat(this->renderer, x, y);
}

void GameState::initBonusTrophy(FILE *level_file)
{
    float x, y;
    fscanf(level_file, "TROPHY: %f %f\n", &x, &y);
    this->bonusTrophy = new BonusTrophy(this->renderer, x, y);
}

void GameState::initLevel(int level_number)
{
    char levelPath[20];
    sprintf(levelPath, "Levels/Level_%d.txt", level_number);

    FILE *levelFile = fopen(levelPath, "r");
    if (levelFile == NULL)
    {
        printf("Cant open file: %s\n", levelPath);
    }

    this->initPlatforms(levelFile);
    this->initLadders(levelFile);
    this->initDonkey(levelFile);
    this->initBarrels(levelFile);
    this->initCat(levelFile);
    this->initBonusTrophy(levelFile);
    this->initPlayer(levelFile);

    fclose(levelFile);
}

void GameState::renderPlatforms(SDL_Renderer* renderer)
{
    for (int i = 0; i < this->platformCount; i++)
    {
        this->platforms[i]->render(renderer);
    }
}

void GameState::renderLadders(SDL_Renderer* renderer)
{
    for (int i = 0; i < this->ladderCount; i++)
    {
        this->ladders[i]->render(renderer);
    }
}

void GameState::renderBarrels(SDL_Renderer *renderer)
{
    for (int i = 0; i < this->barrelCount; i++)
    {
        this->barrels[i]->render(renderer);
    }
}

void GameState::spawnBarrels(const float& dt)
{
    if(this->donkey->getBarrelReady(dt))
    {
        if(this->barrelCount < this->maxBarrels)
        {
            this->barrels[this->barrelCount] = new Barrel(
                this->renderer, 
                this->donkey->getPosition().x, 
                this->donkey->getPosition().y
            );
            this->barrelCount++;
        }
    }
}

void GameState::deleteBarrel(int barrel_index)
{
    delete this->barrels[barrel_index];
    
    for (int i = barrel_index; i < this->barrelCount - 1; i++)
    {
        this->barrels[i] = this->barrels[i + 1];
    }

    this->barrelCount--;
}

void GameState::updateBarrels(const float& dt)
{
    for (int i = 0; i < this->barrelCount; i++)
    {
        this->barrels[i]->update(dt);

        if(this->barrels[i]->getOutOfBounds())
        {
            this->deleteBarrel(i);
            i--;
        }
    }
}

void GameState::changeLevel(int level_number)
{
    if(this->currentLevel != level_number)
    {
        this->currentLevel = level_number;
        this->initLevel(level_number);
        this->updateLevelText();
    }
}

void GameState::initGui()
{
    this->initTexts();
    this->initLivesCounter();
    this->initContinueText();
    this->initSaveScoreText();
}

void GameState::updateGUI(const float& dt)
{
   this->updateTimerText(dt);
   this->updateBonusPoints(dt);
}

void GameState::renderGUI(SDL_Renderer* renderer)
{
    this->guiManager->renderTexts(renderer);
    this->renderLivesCounter(renderer);
    if(this->lostLife && !this->lostGame)
        this->renderContinueText(renderer);
    if (this->lostGame)
        this->renderSaveScoreText(renderer);

    this->renderBonusPoints(renderer);
}

void GameState::initTexts()
{
    this->timerTxt = this->guiManager->addScreenText("timer", CHARSET_CHAR_W, CHARSET_CHAR_H, MAGENTA, 2, {20, 20});
    this->scoreTxt = this->guiManager->addScreenText("score", CHARSET_CHAR_W, CHARSET_CHAR_H, GREEN, 2, {20, 50});
    this->levelTxt = this->guiManager->addScreenText(this->levelText, CHARSET_CHAR_W, CHARSET_CHAR_H, RED, 2, {1120, 20});
    this->updateLevelText();
    this->updateScoreText();
    this->initBonusPointsText();
}

void GameState::updateTimerText(const float& dt)
{
    this->timer += dt;

    int elapsedSeconds = (int)this->timer;
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    int milliseconds = (int)((this->timer - elapsedSeconds) * 100);
    char timerText[20];
    sprintf_s(timerText, "%02d.%02d.%02d", minutes, seconds, milliseconds);
    this->guiManager->updateText(timerTxt, timerText);
}

void GameState::updateScoreText()
{
    char scoreText[20];
    sprintf_s(scoreText, "score:%04d", this->score);
    this->guiManager->updateText(scoreTxt, scoreText);
}

void GameState::initBonusPointsText()
{
    this->bonusTextCount = 0;
    this->bonusTexts = new BonusText*[this->maxBonusTexts];
    sprintf_s(this->barrelBonusPoints, sizeof(this->barrelBonusPoints), "%d", BARREL_BONUS_POINTS);
    sprintf_s(this->trophyBonusPoints, sizeof(this->trophyBonusPoints), "%d", TROPHY_BONUS_POINTS);
}

void GameState::createBonusText(int index, const char *text, float lifetime)
{
    this->bonusTexts[index] = new BonusText(
        text, lifetime, this->renderer,
        CHARSET_CHAR_W, CHARSET_CHAR_H, GREEN, 2,
        {(int)this->player->getPosition().x,
         (int)this->player->getPosition().y - 5});
}

void GameState::addBonusPointsText(const char* text, float lifetime)
{
    if(this->bonusTextCount >= this->maxBonusTexts)
    {
        deleteBonusPointsText(0);
        this->createBonusText(0, text, lifetime);
    }
    else
    {
        this->createBonusText(this->bonusTextCount, text, lifetime);
        this->bonusTextCount++;
    }
}

void GameState::addBonusPoints(int points)
{
    this->score += points;
    this->updateScoreText();
}

void GameState::updateBonusPoints(const float& dt)
{
    for (int i = 0; i < this->bonusTextCount; i++)
    {
        if(this->bonusTexts[i]->getLifetimeExpired(dt)) 
            deleteBonusPointsText(i);
    }
}

void GameState::deleteBonusPointsText(int index)
{
    delete this->bonusTexts[index];

    for (int i = index; i < this->bonusTextCount - 1; i++)
    {
        this->bonusTexts[i] = this->bonusTexts[i + 1];
    }

    this->bonusTextCount--;
}

void GameState::renderBonusPoints(SDL_Renderer *renderer)
{
    for (int i = 0; i < this->bonusTextCount; i++)
        this->bonusTexts[i]->renderText(renderer);
}

void GameState::updateLevelText()
{
    sprintf_s(this->levelText, sizeof(this->levelText), "level: %d", this->currentLevel);
    this->guiManager->updateText(levelTxt, this->levelText);
}

void GameState::initLivesCounter()
{
    TextureManager::loadSprite(HEART_SPRITE_PATH, this->renderer, &heart);
}

void GameState::updateCollision(const float& dt)
{
    //SDL_FPoint calculatedVelocity = this->player->getVelocity();
    int ladderCollisionCount = 0;

    /*
    SDL_FRect futurePosition = {
        this->player->getPosition().x + this->player->getVelocity().x * dt,
        this->player->getPosition().y + this->player->getVelocity().y * dt,
        this->player->getHitboxRect().w,
        this->player->getHitboxRect().h};*/

    if (!this->player->getIsClimbing())
    {
        for (int i = 0; i < this->platformCount; i++)
        {
            if (this->player->isColliding(this->platforms[i]->getHitboxRect()))
            {
                if (this->player->getHitboxRect().y < this->platforms[i]->getHitboxRect().y && this->player->getHitboxRect().y + this->player->getHitboxRect().h < this->platforms[i]->getHitboxRect().y + this->platforms[i]->getHitboxRect().h && !this->player->getIsClimbing()) // collision from above the platform
                {
                    this->player->setPosition(
                        this->player->getPosition().x,
                        this->platforms[i]->getHitboxRect().y - this->player->getHitboxRect().h);
                    this->player->setInAir(false);
                }
                else if (this->player->getHitboxRect().y > this->platforms[i]->getHitboxRect().y && !this->player->getIsClimbing()) // collision from below the platform
                {
                    this->player->setPosition(
                        this->player->getPosition().x,
                        this->platforms[i]->getHitboxRect().y + this->platforms[i]->getHitboxRect().h);
                    this->player->stopVerticalVelocity();
                }

                // horizontal collision
                if (this->player->getInAir())
                {
                    if (this->player->getHitboxRect().x < this->platforms[i]->getHitboxRect().x && this->player->getVelocity().x > 0 && this->player->getVelocity().x > 0) // collision from left side
                    {
                        this->player->setPosition(this->platforms[i]->getPosition().x - this->player->getHitboxRect().w, this->player->getPosition().y);
                        this->player->stopHorizontalVelocity();
                    }
                    else if (this->player->getHitboxRect().x >
                                 this->platforms[i]->getHitboxRect().x + this->platforms[i]->getHitboxRect().w - 2.f &&
                             this->player->getVelocity().x < 0) // collision from right side
                    {
                        this->player->setPosition(this->platforms[i]->getPosition().x + this->platforms[i]->getHitboxRect().w, this->player->getPosition().y);
                        this->player->stopHorizontalVelocity();
                    }
                }
            }
        }
    }

    for (int j = 0; j < this->barrelCount; j++)
    {
        bool isOnPlatform = false;

        for (int i = 0; i < this->platformCount; i++)
        {
            SDL_FRect platformHitbox = this->platforms[i]->getHitboxRect();
            platformHitbox.y -= 2.f;

            if (this->barrels[j]->isColliding(platformHitbox))
            {
                isOnPlatform = true;

                this->barrels[j]->setPosition(
                    this->barrels[j]->getPosition().x,
                    this->platforms[i]->getHitboxRect().y - this->barrels[j]->getHitboxRect().h);
                if (this->barrels[j]->getInAir())
                {
                    this->barrels[j]->swapDirection();
                    this->barrels[j]->setInAir(false);
                    this->barrels[j]->stopVerticalVelocity();
                }
            }
        }

        if (!isOnPlatform)
        {
            this->barrels[j]->setInAir(true);
        }
    }

    // ladder collision
    for (int i = 0; i < this->ladderCount; i++)
    {
        if (this->player->isColliding(this->ladders[i]->getHitboxRect()))
        {
            SDL_FRect playerHitbox = this->player->getHitboxRect();
            SDL_FRect ladderHitbox = this->ladders[i]->getHitboxRect();

            int playerBottom = playerHitbox.y + playerHitbox.h;
            int ladderTop = ladderHitbox.y;
            int ladderBottom = ladderHitbox.y + ladderHitbox.h;

            // if the ladder is above the player
            if(playerBottom >= ladderTop + 4.f)
            {
                this->player->setCanClimbUp(true);
                puts("can climb up");
            } 
            // if the ladder is below the player
            else if(playerBottom <= ladderTop + 4.f)
            {
                this->player->setCanClimbDown(true);
                puts("can climb down");
            }



            if (playerBottom <= ladderTop - 5.f)
            {
                this->player->setCanClimbUp(false);
                puts("can't climb up anymore");
            }
            if(playerBottom >= ladderBottom - 5.f)
            {
                this->player->setCanClimbDown(false);
                this->player->setCanClimb(false); // naprawic to, by nie trzeba tego bylo tak partiowac
                puts("can't climb down anymore");
            }

            ladderCollisionCount++;
            this->player->setCanClimb(true);
        }
    }
    // cant climb if not colliding with any ladder
    if(ladderCollisionCount == 0)
    {
        this->player->setCanClimb(false); // apparently jest wazne gdy nie ma tego to moge przelatywac przez platformy gdy climbuje w dol
        this->player->setCanClimbUp(false);
        this->player->setCanClimbDown(false);
    }


    // barrel collision
    for (int i = 0; i < barrelCount; i ++)
    {
        SDL_FRect barrelHitbox = this->barrels[i]->getHitboxRect();

        // direct collision
        if (this->player->isColliding(barrelHitbox))
        {
            --this->heartCount;
            this->lostLife = true;
            if (this->heartCount <= 0)
            {
                this->gameOver();
                return;
            }
        }
        // jumping over barrel
        else if(this->barrels[i]->getBonusPointsAvailable())
        {
            barrelHitbox.y -= this->player->getHitboxRect().h;
            barrelHitbox.h += this->player->getHitboxRect().h;
            if (this->player->isColliding(barrelHitbox))
            {
                this->addBonusPoints(BARREL_BONUS_POINTS);
                this->addBonusPointsText(this->barrelBonusPoints, 1.f);
                this->barrels[i]->setBonusPointsAvailable(false);
            }
        }
    }

    // cat collision
    if(this->player->isColliding(this->cat->getHitboxRect()))
    {
        this->nextLevel();
    }

    // trophy collision
    if(this->bonusTrophy != NULL)
    {
        if(this->player->isColliding(this->bonusTrophy->getHitboxRect()))
        {
            this->addBonusPoints(TROPHY_BONUS_POINTS);
            this->addBonusPointsText(this->trophyBonusPoints, 2.f);
            delete this->bonusTrophy;
            this->bonusTrophy = NULL;
        }
    }

    // collision with screen bounds
    if(this->player->getPosition().x < 0.f)
    {
        this->player->setPosition(0.f, this->player->getPosition().y);
        this->player->stopHorizontalVelocity();
    }
    else if(this->player->getPosition().x + this->player->getHitboxRect().w > SCREEN_WIDTH)
    {
        this->player->setPosition(SCREEN_WIDTH - this->player->getHitboxRect().w, this->player->getPosition().y);
        this->player->stopHorizontalVelocity();
    }
}

void GameState::updateInput()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_1])
    {
        this->changeLevel(1);
    } 
    else if(state[SDL_SCANCODE_2])
    {
        this->changeLevel(2);
    }
    else if (state[SDL_SCANCODE_3])
    {
        this->changeLevel(3);
    }
    if(this->lostLife && state[SDL_SCANCODE_C] && !this->lostGame)
    {
        this->lostLife = false;
        this->initLevel(this->currentLevel);
    }
    if(this->lostGame && state[SDL_SCANCODE_S])
    {
        this->game->saveScore(this->score);
    }
}

void GameState::update(const float& dt) 
{ 
    this->updateInput();

    if(!this->lostLife)
    {
        this->updateGUI(dt);
        this->player->update(dt);
        this->spawnBarrels(dt);
        this->donkey->update(dt);
        this->updateBarrels(dt);

        this->updateCollision(dt);
    }
}

void GameState::renderLivesCounter(SDL_Renderer *renderer)
{
    for (int i = 0; i < this->heartCount; i++)
        TextureManager::renderTexture(renderer, &heart, 
        SCREEN_WIDTH_MIDDLE - this->heartCount * heart.width / 2 
        + i * (heart.width), 20);
}

void GameState::initContinueText()
{
    this->continueText = new ScreenText("Press C to continue", this->renderer, CHARSET_CHAR_W,
        CHARSET_CHAR_H, RED, 2, {0, 0});
    this->continueText->centerText();
}

void GameState::renderContinueText(SDL_Renderer *renderer)
{
    this->continueText->renderText(renderer);
    this->guiManager->renderText(this->scoreTxt, renderer, SCREEN_WIDTH_MIDDLE - 90, SCREEN_HEIGHT_MIDDLE + 20);
}

void GameState::initSaveScoreText()
{
    this->saveScoreText = new ScreenText("Press S to save your score | M to return to menu", this->renderer, CHARSET_CHAR_W,
        CHARSET_CHAR_H, YELLOW, 2, {0, 0});
    this->saveScoreText->centerText();
}

void GameState::renderSaveScoreText(SDL_Renderer *renderer)
{
    this->saveScoreText->renderText(renderer);
}

void GameState::nextLevel()
{
    this->score += 1000;
    this->updateScoreText();
    
    if(this->currentLevel < 3)
        this->changeLevel(this->currentLevel + 1);
    else 
        this->changeLevel(1);

    for (int i = 0; i < this->bonusTextCount; i++)
        delete this->bonusTexts[i];
}

void GameState::gameOver()
{
    this->renderSaveScoreText(this->renderer);
    this->lostGame = true;
}

void GameState::renderLevel(SDL_Renderer *renderer)
{
    this->renderPlatforms(renderer);
    this->renderLadders(renderer);
    this->renderBarrels(renderer);
    this->donkey->render(renderer);
    this->barrelSet->render(renderer);
    this->cat->render(renderer);
    if(this->bonusTrophy != NULL)
        this->bonusTrophy->render(renderer);
}

void GameState::render(SDL_Renderer* renderer) 
{
    this->renderLevel(renderer);

    this->player->render(renderer);

    this->renderGUI(renderer);
}
