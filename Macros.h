#pragma once

// Window settings
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH_MIDDLE SCREEN_WIDTH / 2
#define SCREEN_HEIGHT_MIDDLE SCREEN_HEIGHT / 2
#define WINDOW_TITLE "King Donkey"
#define FPS_CAP 60;

// Player settings
#define INITIAL_PLAYER_LIVES 3
#define PLAYER_HORIZONTAL_SPEED 120.f
#define PLAYER_CLIMB_SPEED 130.f
#define PLAYER_JUMP_FORCE -210.f
#define PLAYER_GRAVITY 150.f
#define MOVE_LEFT -1
#define MOVE_RIGHT 1
#define CLIMB_UP -1
#define CLIMB_DOWN 1
#define CLIMB_NONE 0
//#define PLAYER_HITBOX_OFFSET_X 10
//#define PLAYER_HITBOX_OFFSET_Y 2
#define PLAYER_HITBOX_OFFSET {15.f, 2.f, 30.f, 2.f}
#define NO_HITBOX_OFFSET {0.f, 0.f, 0.f, 0.f}

// Barrel Settings
#define BARREL_HORIZONTAL_SPEED 70.f
#define BARREL_GRAVITY 150.f

// Points settings
#define BARREL_BONUS_POINTS 100
#define TROPHY_BONUS_POINTS 700

// File paths
//#define PLAYER_SPRITE_PATH "Sprites/Characters/Player/reimuidle.bmp"
#define PLAYER_IDLE_SPRITE_PATH "Sprites/Characters/Player/dog_idle.bmp"
#define PLAYER_CLIMB_SPRITE_PATH "Sprites/Characters/Player/dog_climb.bmp"
#define HEART_SPRITE_PATH "Sprites/GUI/heart.bmp"
#define PLATFORM_SPRITE_PATH "Sprites/Level/platform.bmp"
#define LADDER_SPRITE_PATH "Sprites/Level/ladder.bmp"
#define DONKEY_SPRITE_PATH "Sprites/Characters/Donkey/donkey.bmp"
#define BARREL_SPRITE_PATH "Sprites/Level/barrel.bmp"
#define BARREL_SET_SPRITE_PATH "Sprites/Level/barrel_set.bmp"
#define CAT_SPRITE_PATH "Sprites/Characters/Cat/cat.bmp"
#define BONUS_TROPHY_SPRITE_PATH "Sprites/Level/bonus_trophy.bmp"
#define CHARSET_FILE_PATH "Charsets/cs8x8_transparent.bmp"
#define SCORES_FILE_PATH "scores.txt"

// Charset settings
#define CHARSET_CHAR_W 8
#define CHARSET_CHAR_H 8
#define WHITE {255, 255, 255}
#define RED {255, 0, 0}
#define GREEN {0, 255, 0}
#define MAGENTA {255, 0, 255}
#define YELLOW {204, 204, 0}

// Level settings
#define FIRST_LEVEL 1

// Structs
struct Sprite
{
    SDL_Texture *texture;
    SDL_Point position;
    int width;
    int height;
};