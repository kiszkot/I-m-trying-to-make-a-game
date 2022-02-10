#pragma once
#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {

public:

    Vector2D position;
    Vector2D velocity;
    Vector2D target;
    Vector2D previousPos;

    int width = 32;
    int height = 32;
    int scale = 1;

    int whereTo = 4;

    int speed = 3;

    TransformComponent() {
        position.x = 0.0;
        position.y = 0.0;
    }

    TransformComponent(int sc) {
        position.x = 0.0;
        position.y = 0.0;
        scale = sc;
    }

    TransformComponent(double x, double y) {
        position.x = x;
        position.y = y;
    }

    TransformComponent(double x, double y, int h, int w, int sc) {
        position.x = x;
        position.y = y;
        target.x = x;
        target.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
        if(position.x != target.x || position.y != target.y) {
            moveToPosition(target);
        } else {
            position = roundPosition(position);
            previousPos = position;
            velocity.x = 0;
            velocity.y = 0;
        }
        /*
        velocity.Normalize();
        position.x += double (velocity.x * speed);
        position.y += double (velocity.y * speed);
        */
    }

    void moveToPosition(Vector2D to) {
        switch(whereTo) {
            case 0:
                position.y -= 1;
                break;
            case 1:
                position.x += 1;
                break;
            case 2:
                position.y += 1;
                break;
            case 3:
                position.x -= 1;
                break;
            default:
                break;
        }
    }

    Vector2D selectTargetPosition() {
        target.x = position.x;
        target.y = position.y;
        if(velocity.x == 1) {
            target.x = position.x + width;
        } else if(velocity.x == -1) {
            target.x = position.x - width;
        } else if(velocity.y == 1) {
            target.y = position.y + height;
        } else if(velocity.y == -1) {
            target.y = position.y - height;
        }
        return target;
    }

    /**
     * 0 - up
     * 1 - left
     * 2 - down
     * 3 - right
     * **/
    void selectTargetPosition(int select) {
        if(target.x == position.x && target.y == position.y) {
            target.x = position.x;
            target.y = position.y;
            switch(select) {
                case 0:
                    target.y = position.y - 32;
                    break;
                case 1:
                    target.x = position.x + 32;
                    break;
                case 2:
                    target.y = position.y + 32;
                    break;
                case 3:
                    target.x = position.x - 32;
                    break;
                default:
                    break;
            }
            previousPos = roundPosition(position);
            target = roundPosition(target);
            whereTo = select;
        }
    }

    Vector2D roundPosition(Vector2D pos) {
        pos.x = int(pos.x);
        pos.y = int(pos.y);
        int vertical = int(pos.y) % 32;
        int horizontal = int(pos.x) % 32;
        if(horizontal != 0) pos.x -= horizontal;
        if(vertical != 0) pos.x -= vertical;
        return pos;
    }

};