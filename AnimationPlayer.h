#pragma once
#include "TextureManager.h"
class AnimationPlayer
{
private:
    class Animation
    {
    private:
        SDL_Texture *sheet;
        float frameDuration;
        int frames;
        int currentFrame;
        int frameWidth;
        int frameHeight;
        float frameTime;
        bool isPingPong;
        int direction = 1;

    public:
        Animation(const char* sheet_file, SDL_Renderer* renderer, float frame_duration, 
            int frames, int frame_height, int frame_width, bool ping_pong)
            : sheet(sheet), frameDuration(frame_duration), frames(frames), currentFrame(0), frameTime(0.f),
              frameHeight(frame_height), frameWidth(frame_width), isPingPong(ping_pong) 
              {
                this->sheet = TextureManager::loadTexture(sheet_file, renderer);
              }
        ~Animation()
        {
            SDL_DestroyTexture(this->sheet);
        };

        void resetAnimation()
        {
            this->currentFrame = 0;
            this->frameTime = 0.f;
        }

        void repeatBackwards(const float)
        {
        }

        void updateAnimation(const float &dt)
        {
            this->frameTime += dt;
            if (this->frameTime >= this->frameDuration)
            {
                this->frameTime = 0.f;
                this->currentFrame += direction;
                if (this->currentFrame >= this->frames)
                {
                    if (this->isPingPong)
                    {
                        this->direction = -1;
                        this->currentFrame = this->frames - 1;
                    }
                    else
                    {
                        this->resetAnimation();
                    }
                }
                else if (this->currentFrame < 0)
                {
                    if (this->isPingPong)
                    {
                        this->direction = 1;
                        this->currentFrame = 0; // Start from the first frame
                    }
                    else
                    {
                        this->resetAnimation();
                    }
                }
            }
        }

        void render(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flipType)
        {
            SDL_Rect srcRect = {currentFrame * frameWidth, 0, frameWidth, frameHeight};
            SDL_Rect dstRect = {x, y, frameWidth, frameHeight};
            SDL_RenderCopyEx(renderer, this->sheet, &srcRect, &dstRect, 0.0, NULL, flipType);
        }
    };

    SDL_Renderer* renderer;
    Animation** animations;
    int animationCount;
    int currentAnimation;
    SDL_RendererFlip flipType;

public:
    AnimationPlayer(int animation_count, SDL_Renderer* renderer);
    ~AnimationPlayer();

    void addAnimation(int index, const char *sheet_file, float frame_duration,
        int frames, int frame_height, int frame_width, bool ping_pong);
    void playAnimation(int index);
    void flipAnimation();
    void removeFlip();
    void update(const float &dt);
    void render(SDL_Renderer *renderer, int pos_x, int pos_y);
};

