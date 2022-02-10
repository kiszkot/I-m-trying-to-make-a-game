#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component {

public: 

    TransformComponent * transform;
    SpriteComponent * sprite;

    void init() override {
        transform = & entity -> getComponent<TransformComponent>();
        sprite = & entity -> getComponent<SpriteComponent>();
    }

    void update() override {
        const Uint8 * keystates = SDL_GetKeyboardState(NULL);
        if(keystates[SDL_SCANCODE_W]) {
            transform -> selectTargetPosition(0);
        } else if(keystates[SDL_SCANCODE_A]) {
            transform -> selectTargetPosition(3);
        } else if(keystates[SDL_SCANCODE_S]) {
            transform -> selectTargetPosition(2);
        } else if(keystates[SDL_SCANCODE_D]) {
            transform -> selectTargetPosition(1);
        } else if(keystates[SDL_SCANCODE_ESCAPE]) {
            user_quit.type = SDL_QUIT;
            SDL_PushEvent(&user_quit);
        }
/*
        if(Game::event.type == SDL_KEYDOWN) {
            switch(Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform -> selectTargetPosition(0);
                    transform -> velocity.y = -1;
                    // sprite -> Play("Walk")
                    break;
                case SDLK_a:
                    transform -> selectTargetPosition(3);
                    transform -> velocity.x = -1;
                    // sprite -> Play("Walk")
                    sprite -> spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_s:
                    transform -> selectTargetPosition(2);
                    transform -> velocity.y = 1;
                    // sprite -> Play("Walk")
                    break;
                case SDLK_d:
                    transform -> selectTargetPosition(1);
                    transform -> velocity.x = 1;
                    // sprite -> Play("Walk")
                    break;
                case SDLK_ESCAPE:
                    user_quit.type = SDL_QUIT;
                    SDL_PushEvent(&user_quit);
                    break;
                default:
                    break;
            }
        }

        if(Game::event.type == SDL_KEYUP) {
            switch(Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform -> velocity.y = 0;
                    sprite -> Play("Idle");
                    break;
                case SDLK_a:
                    transform -> velocity.x = 0;
                    sprite -> Play("Idle");
                    sprite -> spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_s:
                    transform -> velocity.y = 0;
                    sprite -> Play("Idle");
                    break;
                case SDLK_d:
                    transform -> velocity.x = 0;
                    sprite -> Play("Idle");
                    break;
                default:
                    break;
            }
        } */
    }

private:
    SDL_Event user_quit;

};