#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL2/SDL.h>
#include <string>

class TileComponent : public Component {

public:

    TransformComponent * transform;
    SpriteComponent * sprite;

    SDL_Rect tileRect;
    int tileID;
    std::string path;
    int xpos = 0;
    int ypos = 0;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        path = "assets/tileMap.png";

        switch(tileID) {
            case 0:
                xpos = 0;
                ypos = 0;
                break;
            case 1:
                xpos = 1;
                ypos = 0;
                break;
            case 2:
                xpos = 2;
                ypos = 0;
            default:
                break;
        }
    }

    void init() override {
        entity -> addComponent<TransformComponent>(double(tileRect.x), double(tileRect.y), tileRect.w, tileRect.h, 1);
        transform = & entity -> getComponent<TransformComponent>();

        entity -> addComponent<SpriteComponent>(path.c_str(), xpos, ypos);
        sprite = & entity -> getComponent<SpriteComponent>();
    }


};