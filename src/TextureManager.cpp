#include "TextureManager.hpp"
#include <stdio.h>

/**
 * Loads the given texture and frees the surface
 * **/

SDL_Texture * TextureManager::LoadTexture(const char * fileName) {

    SDL_Surface * tmpSurface = IMG_Load(fileName);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture * texture, SDL_Rect source, SDL_Rect destination) {
    SDL_RenderCopy(Game::renderer, texture, &source, &destination);
}