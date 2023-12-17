#pragma once

// Window settings
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "King Donkey"
#define FPS_CAP 60;

// Player settings
#define PLAYER_HORIZONTAL_SPEED 120.f
#define PLAYER_CLIMB_SPEED 2.f
#define PLAYER_JUMP_FORCE -3.f
#define PLAYER_GRAVITY 5.f
#define CLIMB_UP -1
#define CLIMB_DOWN 1
#define CLIMB_NONE 0

// File paths
#define PLAYER_SPRITE_PATH "Sprites/Characters/Player/reimuidle.bmp"
#define PLATFORM_SPRITE_PATH "Sprites/Level/platform.bmp"
#define LADDER_SPRITE_PATH "Sprites/Level/ladder.bmp"

// Structs
struct Sprite
{
    SDL_Texture *texture;
    SDL_Point position;
    int width;
    int height;
};