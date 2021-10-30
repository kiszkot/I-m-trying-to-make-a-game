#pragma once

#include "Components.hpp"
#include "TransformComponent.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {

public:

    SpriteComponent() = default;

    // Single texture
    SpriteComponent(const char * path) {
        setTexture(path);
    }

    // Animated texture
    SpriteComponent(const char * path, bool anim, int numberOfFrames) {
        setTexture(path);
        if(anim) numberAnimFrames = numberOfFrames * 32;
        isAnimated = anim;
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

        srcRect.x = x * 32;
        srcRect.y = y * 32;
        srcRect.h = 32;
        srcRect.w = 32;
    }

    void update() override {

        destRect.h = transform -> height * transform -> scale;
        destRect.w = transform -> width * transform -> scale;

        if(isAnimated) {
            srcRect.x = currentAnimFrame;
            animate();
        }

        destRect.x = int (transform -> position.x);
        destRect.y = int (transform -> position.y);
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    void animate() {
        currentAnimFrame += 32;
        if(currentAnimFrame > numberAnimFrames) currentAnimFrame = 0;
    }

    void debug() {
        printf("%d , %d - for sprite\n", srcRect.x, srcRect.y);
    }


private:

    TransformComponent * transform;
    SDL_Texture * texture;

    SDL_Rect srcRect, destRect;
    
    int numberAnimFrames = 0; // number of animation frames
    int currentAnimFrame = 0;
    bool isAnimated = false;

    int x = 0;
    int y = 0;    

};