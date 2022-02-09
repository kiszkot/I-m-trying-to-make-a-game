#pragma once

#include "Components.hpp"
#include "TransformComponent.hpp"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>
#include <map>

class SpriteComponent : public Component {

public:

    int y = 0; // animIndex

    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    // Single texture
    SpriteComponent(const char * path) {
        setTexture(path);
    }

    /**
     * For animated textures a separate texture file is needed
     * The texture can be static and will stay on first frame of the aimation if @animate is set to false
     * */
    SpriteComponent(const char * path, bool animate) {
        isAnimated = animate;

        Animation idle = Animation(0, 5, 100);
        // Animation walk = Animation(1, 5, 100);

        animations.emplace("Idle", idle);
        // animations.emplace("Walk", walk);

        Play("Idle");
        setTexture(path);
    }

    /*
    * Table of textures
    * int scaled by 32 to select wich texture to use
    * 32 px textures
    * */ 
    SpriteComponent(const char * path, int xpos, int ypos) {
        setTexture(path);
        x = xpos;
        y = ypos;
    }

    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char * path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        transform = &entity -> getComponent<TransformComponent>();

        srcRect.x = x * transform -> width;
        srcRect.y = y * transform -> height;
        srcRect.h = transform -> height;
        srcRect.w = transform -> width;
    }

    void update() override {

        if(isAnimated) {
            srcRect.x = srcRect.w * int ((SDL_GetTicks() / speed) % frames);
        }

        srcRect.y = y * transform -> height;

        destRect.h = transform -> height * transform -> scale;
        destRect.w = transform -> width * transform -> scale;
        destRect.x = int (transform -> position.x);
        destRect.y = int (transform -> position.y);
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    void debug() {
        printf("%d , %d - for sprite\n", srcRect.x, srcRect.y);
    }

    void Play(const char * animName) {
        frames = static_cast<Uint32>(animations[animName].frames);
        y = animations[animName].index;
        speed = static_cast<Uint32>(animations[animName].speed);
    }


private:

    TransformComponent * transform;
    SDL_Texture * texture;

    SDL_Rect srcRect, destRect;
    
    Uint32 frames = 0; // number of animation frames
    Uint32 speed = 100; // Delay between frames
    bool isAnimated = false;

    int x = 0;   

};