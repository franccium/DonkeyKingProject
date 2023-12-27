#pragma once

// Window settings
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "King Donkey"
#define FPS_CAP 60;

// Player settings
#define PLAYER_HORIZONTAL_SPEED 120.f
#define PLAYER_CLIMB_SPEED 130.f
#define PLAYER_JUMP_FORCE -150.f
#define PLAYER_GRAVITY 150.f
#define MOVE_LEFT -1
#define MOVE_RIGHT 1
#define CLIMB_UP -1
#define CLIMB_DOWN 1
#define CLIMB_NONE 0
//#define PLAYER_HITBOX_OFFSET_X 10
//#define PLAYER_HITBOX_OFFSET_Y 2
#define PLAYER_HITBOX_OFFSET {15.f, 2.f, 24.f, 2.f}
#define NO_HITBOX_OFFSET {0.f, 0.f, 0.f, 0.f}

// Barrel Settings
#define MAX_BARREL_COUNT 15
#define BARREL_HORIZONTAL_SPEED 60.f
#define BARREL_GRAVITY 150.f

// File paths
#define PLAYER_SPRITE_PATH "Sprites/Characters/Player/reimuidle.bmp"
#define PLATFORM_SPRITE_PATH "Sprites/Level/platform.bmp"
#define LADDER_SPRITE_PATH "Sprites/Level/ladder.bmp"
#define DONKEY_SPRITE_PATH "Sprites/Characters/Donkey/donkey.bmp"
#define BARREL_SPRITE_PATH "Sprites/Level/barrel.bmp"

// Structs
struct Sprite
{
    SDL_Texture *texture;
    SDL_Point position;
    int width;
    int height;
};

enum PlayerStates
{
    IDLE,
    WALKING,
    JUMPING,
    CLIMBING_DOWN,
    CLIMBING_UP
};