#pragma once
#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"

class TextureManager {

public:
    static SDL_Texture * LoadTexture(const char * fileName);
    static void Draw(SDL_Texture * texurre, SDL_Rect source, SDL_Rect destination);

};

#endif