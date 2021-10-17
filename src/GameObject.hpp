#pragma once

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Game.hpp"

class GameObject {

public:
    GameObject(const char * textureSheet, int x, int y);
    ~GameObject();

    void Update();
    void Render();

private:
    int xpos, ypos;

    SDL_Texture * objTexture;
    SDL_Rect srcRect, destRect;

};

#endif