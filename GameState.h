#pragma once
#include "ScreenState.h"
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "Donkey.h"

class GameState :
    public ScreenState
{
private:
    Player* player;

    Platform** platforms;
    int platformCount;
    Ladder** ladders;
    int ladderCount;

    Donkey* donkey;
    Barrel** barrels;
    int barrelCount;

public:
    GameState(SDL_Renderer* renderer);
    ~GameState();

    void initPlayer();
    void initLevel();
    void initPlatforms();
    void initLadders();
    void initDonkey();
    void initBarrels();

    void renderPlatforms(SDL_Renderer* renderer);
    void renderLadders(SDL_Renderer* renderer);
    void renderLevel(SDL_Renderer* renderer);
    void renderBarrels(SDL_Renderer* renderer);

    void spawnBarrels();
    void deleteBarrel(int barrel_index);
    void updateBarrels(const float& dt);

    void updateCollision(const float& dt);
    void updateInput(const float &dt) override;
    void update(const float& dt) override;
    void render(SDL_Renderer* renderer) override;
};

