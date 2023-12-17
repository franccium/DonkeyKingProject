#pragma once

class Animation
{
private:
	SDL_Texture* sheet;
	float frameDuration;
	int frames;
	int currentFrame;
	float frameTime;

public:
	Animation(SDL_Texture* sheet, float frame_duration, int frames)
        : sheet(sheet), frameDuration(frame_duration), frames(frames), currentFrame(0), frameTime(0.f) {}
    ~Animation() 
    { 
        SDL_DestroyTexture(this->sheet); 
    };

    void resetAnimation()
    {
        this->currentFrame = 0;
        this->frameTime = 0.f;
    }

    void updateAnimation(const float& dt)
    {
        this->frameTime += dt;
        if (this->frameTime >= this->frameDuration)
        {
            this->frameTime = 0.f;
            this->currentFrame++;
            if (this->currentFrame >= this->frames)
                this->resetAnimation();
        }
    }

    void render(SDL_Renderer* renderer, SDL_Rect* src_rect, SDL_Rect* dest_rect)
    {
        /*
        SDL_Rect srcRect = {currentFrame * frameWidth, 0, frameWidth, frameHeight};
        SDL_Rect dstRect = {x, y, frameWidth, frameHeight};*/
        SDL_RenderCopy(renderer, this->sheet, src_rect, dest_rect);
    }
};

class AnimationPlayer
{
	// enum z animacjami, zeby miec ich indexy
    // moze taki sheet jak w remakegierka, i w zaleznosci od state wybieram poczatkowe y animacji w sheet

};

