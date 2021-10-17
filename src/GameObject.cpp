#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char * textureSheet, int x, int y) {
    objTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
    srcRect.x = 0;
}

void GameObject::Update() {
    xpos++;
    //ypos = ypos;
    if(xpos > 800 - 64) xpos = 0;


    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x += 32;
    if(srcRect.x >= 160) srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
