#pragma once
#include "ScreenState.h"
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"

class GameState :
    public ScreenState
{
private:
    Player* player;

    Platform** platforms;
    int platformCount;
    Ladder** ladders;
    int ladderCount;

public:
    GameState(SDL_Renderer* renderer);
    ~GameState();

    void initPlayer();
    void initLevel();
    void initPlatforms();
    void initLadders();

    void renderPlatforms(SDL_Renderer* renderer);
    void renderLadders(SDL_Renderer* renderer);
    void renderLevel(SDL_Renderer* renderer);

    void updateCollision();
    void updateInput(const float &dt) override;
    void update(const float& dt) override;
    void render(SDL_Renderer* renderer) override;
};

