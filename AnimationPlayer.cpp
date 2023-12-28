#include "stdafx.h"
#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(int animation_count, SDL_Renderer* renderer)
    : animationCount(animation_count), currentAnimation(0), renderer(renderer)
{
    this->animations = new Animation *[animation_count];
}

AnimationPlayer::~AnimationPlayer()
{
    for (int i = 0; i < this->animationCount; i++)
    {
        delete this->animations[i];
    }
    delete[] this->animations;
}

void AnimationPlayer::addAnimation(int index, const char *sheet_file, float frame_duration,
    int frames, int frame_height, int frame_width, bool ping_pong)
{
    if(index >= this->animationCount)
        return;

    this->animations[index] = new Animation(sheet_file, this->renderer,
        frame_duration, frames, frame_height, frame_width, ping_pong);

    this->animationCount++;
}

void AnimationPlayer::playAnimation(int index)
{
    if(index != this->currentAnimation)
    {
        this->animations[this->currentAnimation]->resetAnimation();
        this->currentAnimation = index;
    }
}

void AnimationPlayer::flipAnimation()
{
    this->flipType = SDL_FLIP_HORIZONTAL;
}

void AnimationPlayer::removeFlip()
{
    this->flipType = SDL_FLIP_NONE;
}

void AnimationPlayer::update(const float& dt)
{
    this->animations[this->currentAnimation]->updateAnimation(dt);
}

void AnimationPlayer::render(SDL_Renderer* renderer, int pos_x, int pos_y)
{
    this->animations[this->currentAnimation]->render(renderer, pos_x, pos_y, this->flipType);
}