#pragma once
#include "stdafx.h"

class TextureManager{
    public:
    // loads a texture from a bmp file and returns a pointer to the texture
    //static SDL_Texture* loadTexture(const char* file_name, SDL_Renderer* renderer, Sprite* sprite)
    //{
    //    SDL_Surface* surface = SDL_LoadBMP(file_name);
    //    if(surface == NULL)
    //    {
    //        puts("Error: at TextureManager: cannot load bmp file");
    //        return NULL;
    //    }

    //    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    //    if(texture == NULL)
    //    {
    //        puts("Error: at TextureManager: cannot create texture");
    //        return NULL;
    //    }

    //    sprite->texture = texture;
    //    sprite->width = surface->w;
    //    sprite->height = surface->h;

    //    SDL_FreeSurface(surface);

    //    //SDL_QueryTexture(texture, NULL, NULL, &sprite->width, &sprite->height);
    //    return texture;
    //}


    static SDL_Texture* loadTexture(const char *file_name, SDL_Renderer *renderer)
    {
        SDL_Surface *surface = SDL_LoadBMP(file_name);
        if (surface == NULL)
        {
            puts("Error: at TextureManager: cannot load bmp file");
            return NULL;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            puts("Error: at TextureManager: cannot create texture");
            return NULL;
        }

        SDL_FreeSurface(surface);

        return texture;
    }

    // loads a texture from a bmp file and initialises Sprite struct by returning a pointer
    // to the texture and setting its height and width
    static void loadSprite(const char* file_name, SDL_Renderer* renderer, Sprite* sprite)
    {
        SDL_Surface* surface = SDL_LoadBMP(file_name);
        if (surface == NULL)
        {
            puts("Error: at TextureManager: cannot load bmp file");
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            puts("Error: at TextureManager: cannot create texture");
            return;
        }

        sprite->texture = texture;
        sprite->width = surface->w;
        sprite->height = surface->h;

        SDL_FreeSurface(surface);
    }

    // creates a new destRect for the given texture and renders the texture to the screen
    /*static void renderTexture(SDL_Renderer* renderer, const Sprite& sprite) {
        SDL_Rect dstRect = {sprite.position.x, sprite.position.y, sprite.width, sprite.height};

        // sets the rect's width and height to be the same as the width and height
        // of the texture
        // SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, sprite.texture, NULL, &dstRect);
        SDL_RenderPresent(renderer);
    }*/

    // creates a new destRect for the given texture and renders the texture
    static void renderTexture(SDL_Renderer* renderer, const Sprite* sprite) {
      SDL_Rect dstRect = {sprite->position.x, sprite->position.y, sprite->width,
                          sprite->height};

      SDL_RenderCopy(renderer, sprite->texture, NULL, &dstRect);
    }

    // sets a fixed position for the new destRect
    static void renderTexture(SDL_Renderer *renderer, const Sprite *sprite, int pos_x, int pos_y)
    {
        SDL_Rect dstRect = {pos_x, pos_y, sprite->width,
                            sprite->height};

        SDL_RenderCopy(renderer, sprite->texture, NULL, &dstRect);
    }

    static void renderTextureRotated(SDL_Renderer *renderer, const Sprite *sprite, double angle)
    {
        SDL_Rect dstRect = {sprite->position.x, sprite->position.y, sprite->width,
                            sprite->height};

        SDL_RenderCopyEx(renderer, sprite->texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
    }
};